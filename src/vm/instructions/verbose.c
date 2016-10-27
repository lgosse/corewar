/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 17:40:44 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/10 10:56:24 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	ft_verbose4(t_process *process, t_vm *vm)
{
	int		i;
	int		idx;

	i = -1;
	idx = 2;
	ft_printf("%.2x ", vm->memory[(process->pc + 1) % MEM_SIZE]);
	while (++i < OP_TAB.nb_param)
		if (process->param_type[i] == 1)
			ft_printf("%.2x ", vm->memory[(process->pc + idx++) % MEM_SIZE]);
		else if ((process->param_type[i] == 2 &&
			OP_TAB.label_size) || process->param_type[i] == 3)
		{
			ft_printf("%.2x %.2x ", vm->memory[(process->pc + idx) % MEM_SIZE],
			vm->memory[(process->pc + idx + 1) % MEM_SIZE]);
			idx += 2;
		}
		else
		{
			ft_printf("%.2x %.2x %.2x %.2x ",
			vm->memory[(process->pc + idx) % MEM_SIZE],
			vm->memory[(process->pc + idx + 1) % MEM_SIZE],
			vm->memory[(process->pc + idx + 2) % MEM_SIZE],
			vm->memory[(process->pc + idx + 3) % MEM_SIZE]);
			idx += 4;
		}
}

void		ft_verbose3(t_process *process, t_vm *vm)
{
	ft_printf("%.2x ", vm->memory[process->pc % MEM_SIZE]);
	if (!OP_TAB.ocp)
	{
		if (OP_TAB.label_size)
		{
			ft_printf("%.2x %.2x ", vm->memory[(process->pc + 1) % MEM_SIZE],
			vm->memory[(process->pc + 2) % MEM_SIZE]);
		}
		else
		{
			ft_printf("%.2x %.2x %.2x %.2x ",
			vm->memory[(process->pc + 1) % MEM_SIZE],
			vm->memory[(process->pc + 2) % MEM_SIZE],
			vm->memory[(process->pc + 3) % MEM_SIZE],
			vm->memory[(process->pc + 4) % MEM_SIZE]);
		}
	}
	else
		ft_verbose4(process, vm);
	ft_putchar('\n');
}

int			ft_verbose5(t_process *process)
{
	int		adv;

	if (OP_TAB.label_size)
		adv = 3;
	else
		adv = 5;
	return (adv);
}

void		ft_verbose2(t_process *process, t_vm *vm)
{
	int		adv;
	int		i;

	if (!vm->verbose)
		return ;
	adv = 1;
	i = -1;
	if (OP_TAB.ocp)
	{
		while (++i < OP_TAB.nb_param)
			if (process->param_type[i] == 1)
				adv += 1;
			else if (OP_TAB.label_size || process->param_type[i] == 3)
				adv += 2;
			else
				adv += 4;
		adv++;
	}
	else
		adv = ft_verbose5(process);
	ft_printf("\nADV %d (%.4p -> %.4p) ", adv, process->pc,
		process->pc + adv);
	ft_verbose3(process, vm);
}

void		ft_verbose(t_vm *vm, t_process *process)
{
	int		i;

	i = -1;
	if (!vm->verbose)
		return ;
	ft_printf("P %4d | %s", process->id + 1, OP_TAB.name);
	while (++i < OP_TAB.nb_param)
	{
		ft_putchar(' ');
		if ((process->param_type[i] == 1 && OP_TAB.ocp))
			ft_print_reg(process, i);
		else if ((OP_TAB.label_size || process->param_type[i] == 3) &&
			process->instruction != 0)
			ft_print_ind(vm, process, i);
		else
			ft_printf("%d", (int)process->param[i]);
	}
}
