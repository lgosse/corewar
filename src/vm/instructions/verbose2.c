/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 14:29:25 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/22 10:39:02 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_print_ind(t_vm *vm, t_process *process, int i)
{
	if (process->instruction == OPCODE_LD - 1)
		ft_printf("%d", ft_load(vm, 4,
			process->pc + process->param[i] % IDX_MOD));
	else if (process->instruction == OPCODE_LLD - 1)
		ft_printf("%d", ft_load(vm, 4,
			process->pc + process->param[i] % IDX_MOD));
	else if (process->instruction == OPCODE_STI - 1 &&
			process->param_type[i] == 3)
		ft_printf("%d", ft_load(vm, 4,
			process->pc + process->param[i] % IDX_MOD));
	else if (process->instruction == OPCODE_AND - 1 &&
			process->param_type[i] == 3)
		ft_printf("%d", ft_load(vm, 4,
			process->pc + process->param[i] % IDX_MOD));
	else if (process->instruction == OPCODE_LLDI - 1 &&
			process->param_type[i] == 3)
		ft_printf("%d", ft_load(vm, 4,
			process->pc + process->param[i] % IDX_MOD));
	else
		ft_printf("%d", (short)process->param[i]);
}

void	ft_print_reg(t_process *process, int i)
{
	if ((process->instruction + 1 >= OPCODE_AND &&
		process->instruction + 1 <= OPCODE_XOR))
		i == 2 ?
		ft_printf("r%d", (unsigned char)process->param[i]) :
		ft_printf("%d", process->reg[(unsigned char)process->param[i] - 1]);
	else if (process->instruction + 1 == OPCODE_LD ||
			process->instruction + 1 == OPCODE_LLD)
		ft_printf("r%d", (unsigned char)process->param[i]);
	else if (process->instruction + 1 == OPCODE_STI && i > 0)
		ft_printf("%d", process->reg[(unsigned char)process->param[i] - 1]);
	else if ((process->instruction + 1 == OPCODE_LDI ||
			process->instruction + 1 == OPCODE_LLDI))
		i == 2 ?
		ft_printf("r%d", (unsigned char)process->param[i]) :
		ft_printf("%d", process->reg[(unsigned char)process->param[i] - 1]);
	else if (process->instruction + 1 == OPCODE_ST && i == 1)
		ft_printf("%d", (unsigned char)process->param[i]);
	else
		ft_printf("r%d", (unsigned char)process->param[i]);
}
