/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:08:01 by gdannay           #+#    #+#             */
/*   Updated: 2018/06/08 16:16:12 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	t_map	*create_map(char **av, int ac)
{
	t_map	*map;

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		return (NULL);
	map->space = 0;
	map->flag = 0;
	map->dump = -1;
	map->player = NULL;
	map->vm = NULL;
	map->process = NULL;
	return (map);
}

static	int		flag_error(char *str)
{
	ft_dprintf(2, str);
	return (0);
}

static	int		get_flags(t_map *map, char **av, int *i)
{
	while (av[*i] && av[*i][0] && av[*i][0] == '-')
	{
		if (!ft_strcmp(av[*i], "-n"))
			return (1);
		else if (!ft_strcmp(av[*i], "-dump"))
		{
			if (!av[*i + 1] || (av[*i + 1]
				&& (!ft_string_isdigit(av[*i + 1]) || ft_atoi(av[*i + 1]) < 0)))
				return (flag_error("Number of cycles is invalid\n"));
			map->dump = ft_atoi(av[*i + 1]);
			*i += 1;
		}
		else if (!ft_strcmp(av[*i], "-v"))
			map->flag = map->flag | V_FLAG;
		else if (!ft_strcmp(av[*i], "-a"))
			map->flag = map->flag | A_FLAG;
		else
			return (flag_error("Invalid flag\n"));
		*i = *i + 1;
	}
	return (1);
}

int				main(int ac, char **av)
{
	t_map	*map;
	int		i;

	i = 1;
	if (ac < 2)
	{
		ft_dprintf(2,
			"Usage : ./corewar [-a][-v -d N -n N] <champion1.cor> <...>\n");
		return (-1);
	}
	if ((!(map = create_map(av, ac)))
			|| (!(get_flags(map, av, &i)))
			|| (!(map->player = read_av(av, ac, i - 1)))
			|| (!(map->vm = create_vm(map->player)))
			|| (!(map->process = initialize_process(map)))
			|| (!(run_vm(map, 1, 0, NULL))))
		return (free_map(map));
	free_map(map);
	return (0);
}
