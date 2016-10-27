/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 16:31:41 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/10 10:55:47 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ft_aff(t_vm *vm, t_process *process)
{
	if (process->param[0] >= 1 && process->param[0] <= 16 && vm->aff)
		ft_printf("Aff: %c", process->reg[process->param[0] - 1] % 256);
	else
	{
		ft_adv_invalid(process, vm);
		return ;
	}
	if (!vm->verbose && vm->aff)
		ft_putchar('\n');
	ft_verbose2(process, vm);
}
