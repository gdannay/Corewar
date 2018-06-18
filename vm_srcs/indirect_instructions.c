/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:02:25 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/18 15:04:43 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				instruction_ldi(t_vm *vm, t_process *pr)
{
	char	s[4];
	int		p[4];

	ft_bzero(s, 4);
	ft_bzero(p, 4);
	if (pr->cycle < 25)
		return (inst_progress(pr, 10));
	take_opcode(vm->arena[(pr->position + 1) % MEM_SIZE], s, 9);
	p[0] = 1;
	take_params(vm->arena, pr->position + 2, p, s);
	if (check_op(9, s) == ERROR)
		return (inst_done(pr, 2 + p[3]));
	if (s[0] && s[0] == 'r' && p[0] && p[0] >= 1 && p[0] <= 16)
		p[0] = pr->registre[p[0] - 1];
	else if (s[0] && s[0] == 'r')
		return (inst_done(pr, 2 + p[3]));
	if (s[1] && s[1] == 'r' && p[1] && p[1] >= 1 && p[1] <= 16)
		p[1] = pr->registre[p[1] - 1];
	else if (s[1] && s[1] == 'r')
		return (inst_done(pr, 2 + p[3]));
	if (s[0] && s[0] == 'i')
		p[0] = recup_nb_32(vm->arena, pr->position + p[0]) % IDX_MOD;
	(p[2] && p[2] >= 1 && p[2] <= 16) ? pr->registre[p[2] - 1] =
		recup_nb_32(vm->arena, (pr->position + ((p[0] + p[1]) % IDX_MOD))) : 0;
	return (inst_done(pr, 2 + p[3]));
}

int				instruction_sti(t_vm *vm, t_process *pr)
{
	char	s[4];
	int		p[4];

	ft_bzero(s, 4);
	ft_bzero(p, 4);
	if (pr->cycle < 25)
		return (inst_progress(pr, 11));
	take_opcode(vm->arena[(pr->position + 1) % MEM_SIZE], s, 10);
	p[0] = 1;
	take_params(vm->arena, pr->position + 2, p, s);
	if (check_op(10, s) == ERROR)
		return (inst_done(pr, 2 + p[3]));
	if (s[1] && s[1] == 'r' && p[1] >= 1 && p[1] <= 16)
		p[1] = pr->registre[p[1] - 1];
	else if (s[1] && s[1] == 'r')
		return (inst_done(pr, 2 + p[3]));
	if (s[2] && s[2] == 'r' && p[2] >= 1 && p[2] <= 16)
		p[2] = pr->registre[p[2] - 1];
	else if (s[2] && s[2] == 'r')
		return (inst_done(pr, 2 + p[3]));
	if (s[1] && s[1] == 'i')
		p[1] = recup_nb_32(vm->arena, pr->position + p[1]);
	(p[0] && p[0] >= 1 && p[0] <= 16) ? write_arena(vm, pr->registre[p[0] - 1],
			pr->position + ((p[1] + p[2]) % IDX_MOD), pr->color) : 0;
	return (inst_done(pr, 2 + p[3]));
}

static	void	lldi_fill_carry(t_process **pr, t_vm *vm, int *p)
{
	if (p[2] && p[2] >= 1 && p[2] <= 16)
		(*pr)->registre[p[2] - 1] =
			recup_nb_32(vm->arena, (*pr)->position + p[0] + p[1]);
	(*pr)->carry = (p[2] && p[2] >= 1 && p[2] <= 16
		&& !(*pr)->registre[p[2] - 1]) ? 1 : 0;
}

int				instruction_lldi(t_vm *vm, t_process *pr)
{
	char	s[4];
	int		p[4];

	ft_bzero(s, 4);
	ft_bzero(p, 4);
	if (pr->cycle < 50)
		return (inst_progress(pr, 14));
	take_opcode(vm->arena[(pr->position + 1) % MEM_SIZE], s, 13);
	p[0] = 1;
	take_params(vm->arena, pr->position + 2, p, s);
	if (check_op(13, s) == ERROR)
		return (inst_done(pr, 2 + p[3]));
	if (s[0] && s[0] == 'r' && p[0] >= 1 && p[0] <= 16)
		p[0] = pr->registre[p[0] - 1];
	else if (s[0] && s[0] == 'r')
		return (inst_done(pr, 2 + p[3]));
	if (s[1] && s[1] == 'r' && p[1] >= 1 && p[1] <= 16)
		p[1] = pr->registre[p[1] - 1];
	else if (s[1] && s[1] == 'r')
		return (inst_done(pr, 2 + p[3]));
	if (s[0] && s[0] == 'i')
		p[0] = recup_nb_32(vm->arena, pr->position + p[0]);
	lldi_fill_carry(&pr, vm, p);
	return (inst_done(pr, 2 + p[3]));
}
