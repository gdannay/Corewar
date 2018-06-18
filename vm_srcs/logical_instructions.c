/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:00:46 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/18 14:45:09 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	void	logical_fill_carry(t_process **pr, int *p, int val)
{
	if (p[2] && p[2] >= 1 && p[2] <= 16)
	{
		(*pr)->registre[p[2] - 1] = val;
		(*pr)->carry = (p[2] && p[2] >= 1 && p[2] <= 16
				&& !(*pr)->registre[p[2] - 1]) ? 1 : 0;
	}
}

int				instruction_and(t_vm *vm, t_process *pr)
{
	char	s[4];
	int		p[4];

	ft_bzero(s, 4);
	ft_bzero(p, 4);
	if (pr->cycle < 6)
		return (inst_progress(pr, 6));
	take_opcode(vm->arena[(pr->position + 1) % MEM_SIZE], s, 5);
	take_params(vm->arena, pr->position + 2, p, s);
	if (check_op(5, s) == ERROR)
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
		p[0] = recup_nb_32(vm->arena, pr->position + (p[0] % IDX_MOD));
	if (s[1] && s[1] == 'i')
		p[1] = recup_nb_32(vm->arena, pr->position + (p[1] % IDX_MOD));
	logical_fill_carry(&pr, p, p[0] & p[1]);
	return (inst_done(pr, 2 + p[3]));
}

int				instruction_or(t_vm *vm, t_process *pr)
{
	char	s[4];
	int		p[4];

	ft_bzero(s, 4);
	ft_bzero(p, 4);
	if (pr->cycle < 6)
		return (inst_progress(pr, 7));
	take_opcode(vm->arena[(pr->position + 1) % MEM_SIZE], s, 6);
	take_params(vm->arena, pr->position + 2, p, s);
	if (check_op(6, s) == ERROR)
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
		p[0] = recup_nb_32(vm->arena, pr->position + (p[0] % IDX_MOD));
	if (s[1] && s[1] == 'i')
		p[1] = recup_nb_32(vm->arena, pr->position + (p[1] % IDX_MOD));
	logical_fill_carry(&pr, p, p[0] | p[1]);
	return (inst_done(pr, 2 + p[3]));
}

int				instruction_xor(t_vm *vm, t_process *pr)
{
	char	s[4];
	int		p[4];

	ft_bzero(s, 4);
	ft_bzero(p, 4);
	if (pr->cycle < 6)
		return (inst_progress(pr, 8));
	take_opcode(vm->arena[(pr->position + 1) % MEM_SIZE], s, 7);
	take_params(vm->arena, pr->position + 2, p, s);
	if (check_op(7, s) == ERROR)
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
		p[0] = recup_nb_32(vm->arena, pr->position + (p[0] % IDX_MOD));
	if (s[1] && s[1] == 'i')
		p[1] = recup_nb_32(vm->arena, pr->position + (p[1] % IDX_MOD));
	logical_fill_carry(&pr, p, p[0] ^ p[1]);
	return (inst_done(pr, 2 + p[3]));
}
