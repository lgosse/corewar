/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 16:33:02 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/08 16:46:52 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_zjmp(t_vm *vm, t_process *process)
{
	ft_verbose(vm, process);
	if (process->carry == 1)
	{
		if (vm->verbose)
			ft_printf(" OK\n");
		process->pc2 = process->pc + ((short)process->param[0] % IDX_MOD);
		process->pc2 %= MEM_SIZE;
	}
	else
	{
		process->pc2 = (process->pc + 3) % MEM_SIZE;
		if (vm->verbose)
			ft_printf(" FAILED");
		ft_verbose2(process, vm);
	}
}
