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

char *format_params(t_inst *inst, char *line)
{
	int i;
	int j;
	char *new;

	new = malloc(sizeof(char) * ft_strlen(line) + 1);
	ft_bzero(new, ft_strlen(line));
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
		printf("Invalid parameter for instruction %s : no parameters\n", inst->name);
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

int verif_register(t_inst *new, char ***split, char *line)
{
	if (!ft_string_isdigit(line + 1))
	{
		printf("Invalid parameter type register \"%s\" for instruction %s : not a numeric value\n", line + 1, new->name);
		free_split(split);
		return (ERROR);
	}
	if (ft_atoi(line + 1) < 1 || ft_atoi(line + 1) > REG_NUMBER)
	{
		printf("Invalid parameter type register \"%s\" for instruction %s : not in interval [1-%d]\n", line + 1, new->name, REG_NUMBER);
		free_split(split);
		return (ERROR);
	}
	return (1);
}

int verif_direct(t_inst *new, char ***split, char *line)
{
	if (!ft_string_isdigit(line + 1))
	{
		if (line[1] == LABEL_CHAR)
			;
		else
		{
			printf("Invalid parameter type direct \"%s\" for instruction %s : not a numeric value or a label\n", line + 1, new->name);
			free_split(split);
			return (ERROR);
		}
	}
	return (2);
}

int verif_indirect(t_inst *new, char ***split, char *line)
{
	(void)new;
	(void)line;
	(void)split;
	return (8);
}

int verif_nb_params(char ***split_free, char **split, int j)
{
	int i;

	i = -1;
	while (split[++i]) ;
	if (i != op_tab[j].nb_par)
	{
		printf("Invalid parameter %d type register for instruction live\n", op_tab[j].nb_par);
		free_split(split_free);
		return (ERROR);
	}
	return (TRUE);
}

int verif_type(t_inst *new, char ***split, char *line, int i)
{
	if (line[0] == 'r')
		printf("Invalid parameter %d type register for instruction %s\n", i, new->name);
	else if (line[0] == DIRECT_CHAR)
		printf("Invalid parameter %d type direct for instruction %s\n", i, new->name);
	else
		printf("Invalid parameter %d type indirect for instruction %s\n", i, new->name);
	free_split(split);
	return (ERROR);
}

int 		check_params(t_inst *new, char *line, int j)
{
	char **split;
	int i;
	int type;

	i = -1;
	while (++i < 4)
		new->params[i] = NULL;
	if ((line = format_params(new, line)) == NULL)
		return (ERROR);
	split = ft_strsplit(line, SEPARATOR_CHAR);
	if (verif_nb_params(&split, split, j) == ERROR)
		return (ERROR);
	i = -1;
	while (split[++i])
	{
		printf("%s\n", split[i]);
		if (split[i][0] == 'r')
		{
			if ((type = verif_register(new, &split, split[i])) == ERROR)
				return (ERROR);
		}
		else if (split[i][0] == DIRECT_CHAR)
		{
			if ((type = verif_direct(new, &split, split[i])) == ERROR)
				return (ERROR);
		}
		else
		{
			if ((type = verif_indirect(new, &split, split[i])) == ERROR)
				return (ERROR);
		}
		if (!(type & op_tab[j].type_par[i]))
			return (verif_type(new, &split, split[i], i));
		new->params[i] = ft_strdup(split[i]);
	}
	free_split(&split);
	return (TRUE);
}
