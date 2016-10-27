/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 16:31:57 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/09 16:45:58 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_ld(t_vm *vm, t_process *process)
{
	int		adress;

	if (process->param[1] >= 1 && process->param[1] <= 16)
	{
		ft_verbose(vm, process);
		if (process->param_type[0] == T_DIR)
			process->reg[process->param[1] - 1] = process->param[0];
		else
		{
			adress = (process->pc + process->param[0] % IDX_MOD) % MEM_SIZE;
			if (adress < 0)
				adress += MEM_SIZE;
			process->reg[process->param[1] - 1] =
				ft_load(vm, 4, adress);
		}
		process->carry = !process->reg[process->param[1] - 1];
		ft_verbose2(process, vm);
	}
	else
		ft_adv_invalid(process, vm);
}
