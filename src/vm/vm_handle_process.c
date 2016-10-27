/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handle_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 18:27:02 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/13 15:18:29 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_get_all_param(t_vm *vm, t_process *process)
{
	int		i;

	i = 0;
	while (i < OP_TAB.nb_param)
	{
		if (process->param_type[i] == 2 &&
				!OP_TAB.label_size)
		{
			process->param[i] = ft_load(vm, 4, process->pc2);
			process->pc2 += 4;
		}
		else if (process->param_type[i] == 1)
		{
			process->param[i] = (unsigned char)ft_load(vm, 1, process->pc2);
			process->pc2 += 1;
		}
		else
		{
			process->param[i] = (short)ft_load(vm, 2, process->pc2);
			process->pc2 += 2;
		}
		i++;
	}
}

int		ft_check_param(t_process *process, int i)
{
	if (process->param_type[i] == REG_CODE)
		return (OP_TAB.param[i] & T_REG ? 1 : 0);
	else if (process->param_type[i] == DIR_CODE)
		return (OP_TAB.param[i] & T_DIR ? 1 : 0);
	else if (process->param_type[i] == IND_CODE)
		return (OP_TAB.param[i] & T_IND ? 1 : 0);
	else if (process->param_type[i] == 0)
		return (0);
	return (1);
}

int		ft_get_params(t_vm *vm, t_process *process)
{
	int		adv;

	process->pc2 = process->pc + 1;
	if (OP_TAB.ocp)
	{
		if ((adv = ft_get_ocp(vm, process)) > 1)
			return (adv);
	}
	else
	{
		process->param[0] = OP_TAB.label_size ?
			ft_load(vm, 2, process->pc2) :
			ft_load(vm, 4, process->pc2);
		process->pc2 += OP_TAB.label_size ? 2 : 4;
		return (1);
	}
	process->pc2++;
	ft_get_all_param(vm, process);
	return (1);
}

void	ft_print_invalid_ocp(t_vm *vm, t_process *process, int adv)
{
	int		idx;

	if (!vm->verbose)
		return ;
	idx = 2;
	ft_printf("ADV %d (%.4p -> %.4p) %.2x %.2x ", adv, process->pc,
		process->pc + adv, vm->memory[(process->pc) % MEM_SIZE],
		vm->memory[(process->pc + 1) % MEM_SIZE]);
	while (idx < adv)
	{
		ft_printf("%.2x ", vm->memory[(process->pc + idx) % MEM_SIZE]);
		idx++;
	}
	ft_putchar('\n');
}

void	ft_handle_process(t_vm *vm, t_process *process)
{
	int		adv;

	if (--process->cycle_bf_exe == 0)
	{
		if ((adv = ft_get_params(vm, process)) > 1)
		{
			ft_print_invalid_ocp(vm, process, adv);
			if (vm->ncurses)
				ft_erase_pc(vm, process);
			process->pc += adv;
		}
		else
		{
			vm->f[(int)process->instruction](vm, process);
			if (vm->ncurses)
				ft_print_pc(vm, process);
			process->pc = process->pc2;
		}
		process->instruction = -1;
	}
	else if (process->instruction == -1)
		ft_get_instruction(vm, process);
}
