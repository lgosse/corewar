/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 13:51:28 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/09 14:15:06 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int		ft_load(t_vm *vm, int size, int adress)
{
	int		param;

	param = 0;
	while (adress < 0)
		adress += MEM_SIZE;
	if (size == 1)
		param = vm->memory[(adress) % MEM_SIZE];
	else if (size == 2)
	{
		param = ((vm->memory[(adress + 1) % MEM_SIZE]));
		param |= ((vm->memory[(adress + 0) % MEM_SIZE]) << 8);
	}
	else
	{
		param = ((vm->memory[(adress + 3) % MEM_SIZE]));
		param |= ((vm->memory[(adress + 2) % MEM_SIZE]) << 8);
		param |= ((vm->memory[(adress + 1) % MEM_SIZE]) << 16);
		param |= ((vm->memory[(adress + 0) % MEM_SIZE]) << 24);
	}
	return (param);
}
