/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 16:32:22 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/22 10:17:54 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static int	get_param_value(t_process *process, int param, int *val, t_vm *vm)
{
	if (process->param_type[param] == T_REG)
	{
		if (process->param[param] >= 1 && process->param[param] <= 16)
			*val = process->reg[process->param[param] - 1];
		else
			return (0);
	}
	else if (process->param_type[param] == T_DIR)
		*val = (short)process->param[param];
	else
		*val = ft_load(vm, 4, process->pc + process->param[param] % IDX_MOD);
	return (1);
}

void		ft_lldi(t_vm *vm, t_process *process)
{
	int		val1;
	int		val2;
	int		adress;

	if (process->param[2] >= 1 && process->param[2] <= 16)
	{
		if (!get_param_value(process, 0, &val1, vm) ||
			!get_param_value(process, 1, &val2, vm))
		{
			ft_adv_invalid(process, vm);
			return ;
		}
		ft_verbose(vm, process);
		adress = (process->pc + (val1 + val2)) % MEM_SIZE;
		if (vm->verbose)
			ft_printf("\n%7s| -> load from %d + %d = %d (with pc %d)",
			"", val1, val2, val1 + val2, process->pc + (val1 + val2));
		if (adress < 0)
			adress += MEM_SIZE;
		process->reg[process->param[2] - 1] = ft_load(vm, 4, adress);
		process->carry = !process->reg[process->param[2] - 1];
		ft_verbose2(process, vm);
	}
	else
		ft_adv_invalid(process, vm);
}
