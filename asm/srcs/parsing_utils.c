/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 18:04:32 by vferreir          #+#    #+#             */
/*   Updated: 2018/04/26 18:04:33 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

extern t_op op_tab[17];

int		find_next_char(char *str, int i)
{
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	//dprintf(1, "TEST = %d %c\n", str[i], str[i]);
	return (i);
}

int		find_next_space(char *str, int i)
{
	int temp;

	temp = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	if (ft_strlen(str + i) == 0)
	{
		ft_printf("Invalid parameter for instruction %s : no parameters\n", str + temp);
		return (-1);
	}
	return (i);
}

int		fill_label(t_inst *new, char *line)
{
	int		i;
	int		idx;

  idx = -1;
	i = find_next_char(line, 0);
  if (line[i] == ':')
  {
    printf("Label is empty\n");
    return (-1);
  }
	if ((idx = ft_stridx(line, ":")) != (int)ft_strlen(line) && idx > 0 && line[idx - 1] != '%')
	{
		if (new != NULL)
			new->label = ft_strsub(line, i, idx - i);
		i = find_next_char(line, idx + 1);
	}
	return (i);
}

int verif_label(char *line)
{
	int j;
	int i;

	i = -1;
	while (line[++i])
	{
		j = -1;
		while (LABEL_CHARS[++j])
		{
			if (LABEL_CHARS[j] == line[i])
				break ;
		}
		if (j == 37 && (line[i] == ':' || line[i] == '\0'))
			return (TRUE);
		else if (j == 37)
		{
			ft_printf("Label \"%s\" not respect LABEL_CHARS: \"%s\"\n", line, LABEL_CHARS);
			return (ERROR);
		}
	}
	return (TRUE);
}

int take_index_in_op(t_inst *inst, char *line, int size)
{
	char new[size];
	int j;

	ft_strncpy(new, line, size);
	new[size] = '\0';
	j = 0;
	while (ft_strcmp(new, op_tab[j].name))
	{
		j++;
		if (j > 15)
		{
			ft_printf("Invalid instruction \"%s\" : no exist\n", new);
			return (-1);
		}
	}
	inst->code = op_tab[j].code;
	inst->name = ft_strdup(op_tab[j].name);
	return (j);
}
