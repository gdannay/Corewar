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
#include "get_next_line.h"

extern t_op op_tab[17];

char *format_params(char *line)
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
	return (new);
}

int verif_register(char *line)
{
  int t;

  t = 0;
  while (line[++t])
  {
    if (ft_isdigit(line[t]) == 0)
    {
      printf("Syntax error at token [TOKEN][004:014] INSTRUCTION \"%s\"\n", line);
      exit(0);
    }
  }
  if (ft_atoi(line + 1) < 1 || ft_atoi(line + 1) > REG_NUMBER)
  {
    printf("Invalid parameter 0 type register for instruction live\n");
    exit(0);
  }
  return (1);
}

void 		check_params(t_inst *new, char *line, int j)
{
	char **split;
	int i;
	int type;

	(void)new;
	line = format_params(line);
	split = ft_strsplit(line, SEPARATOR_CHAR);
	i = -1;
	while (split[++i]) ;
	if (i != op_tab[j].nb_par)
	{
		printf("Invalid parameter %d type register for instruction live\n", op_tab[j].nb_par);
		exit(0);
	}
	i = -1;
	type = 0;
	while (split[++i])
	{
		printf("%s\n", split[i]);
		if (split[i][0] == 'r')
		{
			type = verif_register(split[i]);
		}
		else if (split[i][0] == DIRECT_CHAR)
		{
			// A FAIRE
			type = 2;
		}
		else if (split[i][0] == LABEL_CHAR)
		{
			// A FAIRE
			type = 8;
		}
		else {
			printf("Error3\n");
			exit(0);
		}

		if (!(type & op_tab[j].type_par[i]))
		{
			printf("Error2\n");
			exit(0);
		}
	}
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
