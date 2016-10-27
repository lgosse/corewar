/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 16:32:41 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/12 08:42:16 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ft_st(t_vm *vm, t_process *process)
{
	int		adress;

	if (process->param[0] >= 1 && process->param[0] <= 16)
	{
		if (process->param_type[1] == 1)
		{
			if (process->param[1] >= 1 && process->param[1] <= 16)
			{
				ft_verbose(vm, process);
				process->reg[process->param[1] - 1] =
					process->reg[process->param[0] - 1];
				ft_verbose2(process, vm);
			}
			else
				ft_adv_invalid(process, vm);
			return ;
		}
		ft_verbose(vm, process);
		adress = (process->pc + (process->param[1] % IDX_MOD)) % MEM_SIZE;
		ft_store(vm, process, adress);
		ft_verbose2(process, vm);
	}
	else
		ft_adv_invalid(process, vm);
}
