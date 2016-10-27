/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_invalid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 13:57:52 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/10 10:56:03 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_adv_invalid(t_process *process, t_vm *vm)
{
	int		adv;
	int		i;

	if (!vm->verbose)
		return ;
	adv = 1;
	i = -1;
	if (g_op_tab[(int)(process->instruction)].ocp)
	{
		while (++i < g_op_tab[(int)(process->instruction)].nb_param)
			if (process->param_type[i] == 1)
				adv += 1;
			else if (g_op_tab[(int)(process->instruction)].label_size ||
				process->param_type[i] == 3)
				adv += 2;
			else
				adv += 4;
		adv++;
	}
	else
		adv = ft_verbose5(process);
	ft_printf("ADV %d (%.4p -> %.4p) ", adv, process->pc,
		(process->pc + adv));
	ft_verbose3(process, vm);
}
