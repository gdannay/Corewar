/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params_verif.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 18:04:20 by vferreir          #+#    #+#             */
/*   Updated: 2018/04/26 18:04:22 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op op_tab[17];

int	verif_register(t_inst *new, char ***split, char *line)
{
	if (!ft_string_isdigit(line + 1))
	{
		ft_printf("Invalid parameter type register \"%s\" for instruction %s : not a numeric value\n", line + 1, new->name);
		free_split(split);
		return (ERROR);
	}
	if (ft_atoi(line + 1) < 1 || ft_atoi(line + 1) > REG_NUMBER)
	{
		ft_printf("Invalid parameter type register \"%s\" for instruction %s : not in interval [1-%d]\n", line + 1, new->name, REG_NUMBER);
		free_split(split);
		return (ERROR);
	}
	return (1);
}

int	verif_direct(t_inst *new, char ***split, char *line)
{
	if (!ft_string_isdigit(line + 1))
	{
		if (line[1] == LABEL_CHAR && verif_label(line + 2))
			;
		else
		{
			ft_printf("Invalid parameter type direct \"%s\" for instruction %s : not a numeric value or a label\n", line + 1, new->name);
			free_split(split);
			return (ERROR);
		}
	}
	return (2);
}

int	verif_indirect(t_inst *new, char ***split, char *line)
{
	if (line[0] == LABEL_CHAR)
	{
		if (verif_label(line + 1) == ERROR)
		{
			free_split(split);
			return (ERROR);
		}
	}
	else if (!ft_string_isdigit(line))
	{
		ft_printf("Invalid parameter type direct \"%s\" for instruction %s : not a numeric value or a label\n", line, new->name);
		free_split(split);
		return (ERROR);
	}
	return (4);
}

int 	verif_nb_params(t_inst *new, char ***split_free, char **split, int j)
{
	int i;

	i = -1;
	while (split[++i]) ;
	if (i != op_tab[j].nb_par)
	{
		ft_printf("Invalid parameter %d type register for instruction %s\n", op_tab[j].nb_par, new->name);
		free_split(split_free);
		return (ERROR);
	}
	return (TRUE);
}

int	verif_type(t_inst *new, char ***split, char *line, int i)
{
	if (line[0] == 'r')
		ft_printf("Invalid parameter %d type register for instruction %s\n", i, new->name);
	else if (line[0] == DIRECT_CHAR)
		ft_printf("Invalid parameter %d type direct for instruction %s\n", i, new->name);
	else
		ft_printf("Invalid parameter %d type indirect for instruction %s\n", i, new->name);
	free_split(split);
	return (ERROR);
}
