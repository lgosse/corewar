/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handle_process2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 19:08:02 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/13 15:20:40 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	ft_getparamtype(t_vm *vm, t_process *process)
{
	process->param_type[0] =
		((unsigned char)(vm->memory[process->pc2 % MEM_SIZE]) >> 6);
	process->param_type[1] =
		((unsigned char)(vm->memory[process->pc2 % MEM_SIZE] & 0x30) >> 4);
	process->param_type[2] =
		((unsigned char)(vm->memory[process->pc2 % MEM_SIZE] & 0xC) >> 2);
}

int			ft_get_ocp(t_vm *vm, t_process *process)
{
	int		i;
	int		adv;
	int		ok;

	i = -1;
	adv = 2;
	ok = 1;
	process->ocp = *(vm->memory + process->pc2 % MEM_SIZE);
	ft_getparamtype(vm, process);
	while (++i < OP_TAB.nb_param)
	{
		if (!ft_check_param(process, i))
			ok = 0;
		if (process->param_type[i] == IND_CODE ||
			(process->param_type[i] == DIR_CODE && OP_TAB.label_size))
			adv += IND_SIZE;
		else if (process->param_type[i] == DIR_CODE && !OP_TAB.label_size)
			adv += DIR_SIZE;
		else if (process->param_type[i] == REG_CODE)
			adv += 1;
	}
	return (ok ? 1 : adv);
}

void		ft_get_instruction(t_vm *vm, t_process *process)
{
	if (vm->memory[process->pc % MEM_SIZE] >= 1 &&
			vm->memory[process->pc % MEM_SIZE] <= 16)
	{
		process->instruction = vm->memory[process->pc % MEM_SIZE] - 1;
		process->cycle_bf_exe = OP_TAB.nb_cycles - 1;
	}
	else
	{
		process->pc2 = process->pc + 1;
		if (vm->ncurses)
			ft_print_pc(vm, process);
		process->pc = process->pc2;
	}
}
