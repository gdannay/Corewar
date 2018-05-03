/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:18:58 by vferreir          #+#    #+#             */
/*   Updated: 2018/04/20 18:18:59 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op op_tab[17];

static char *format_params(t_inst *inst, char *line)
{
	int i;
	int j;
	char *new;

	if ((new = ft_memalloc(sizeof(char) * ft_strlen(line) + 1)) == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (line[++j])
	{
		if (line[j] == COMMENT_CHAR)
			break;
		if (line[j] != ' ' && line[j] != '\t')
		{
			new[i] = line[j];
			i++;
		}
	}
	new[i] = '\0';
	if (ft_strlen(new) == 0)
	{
		ft_printf("Invalid parameter for instruction %s : no parameters\n", inst->name);
		return (NULL);
	}
	return (new);
}

void free_split(char ***split)
{
	int i;
	char **tab;

	tab = *split;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(*split);
}

int 		check_params(t_inst *new, char *line, int j)
{
	char **split;
	int i;
	int type;

	if ((line = format_params(new, line)) == NULL)
		return (ERROR);
	if ((split = ft_strsplit(line, SEPARATOR_CHAR)) == NULL)
		return (ERROR);
	if (verif_nb_params(new, &split, split, j) == ERROR)
		return (ERROR);
	i = -1;
	while (split[++i])
	{
		if (split[i][0] == 'r' && (type = verif_register(new, &split, split[i])) == ERROR)
			return (ERROR);
		if (split[i][0] == DIRECT_CHAR && (type = verif_direct(new, &split, split[i])) == ERROR)
			return (ERROR);
		if (split[i][0] != 'r' && split[i][0] != DIRECT_CHAR && (type = verif_indirect(new, &split, split[i])) == ERROR)
			return (ERROR);
		if (!(type & op_tab[j].type_par[i]))
			return (verif_type(new, &split, split[i], i));
		new->params[i] = ft_strdup(split[i]);
	}
	free_split(&split);
	return (TRUE);
}
