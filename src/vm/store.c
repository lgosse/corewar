/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 13:48:14 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/13 13:24:13 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_graphic_handle(t_vm *vm, int adress)
{
	int		idx;

	idx = 0;
	while (idx < 4)
	{
		if (vm->mem_color[adress + idx] >= 0)
			attron(COLOR_PAIR(vm->mem_color[(adress + idx) % MEM_SIZE]));
		else
			attron(COLOR_PAIR(5));
		mvwprintw(stdscr, ((adress + idx) % MEM_SIZE) / 64 + 2,
			((adress + idx) % MEM_SIZE) % 64 * 3 + 3, "%.2x ",
			vm->memory[(adress + idx) % MEM_SIZE]);
		if (vm->mem_color[(adress + idx) % MEM_SIZE] >= 0)
			attroff(COLOR_PAIR(vm->mem_color[(adress + idx) % MEM_SIZE]));
		else
			attroff(COLOR_PAIR(5));
		idx++;
	}
}

void	ft_store(t_vm *vm, t_process *process, int adress)
{
	int value;

	value = process->reg[process->param[0] - 1];
	if (adress < 0)
		adress = MEM_SIZE + adress;
	vm->memory[(adress + 3) % MEM_SIZE] = value;
	vm->memory[(adress + 2) % MEM_SIZE] = (value >> 8);
	vm->memory[(adress + 1) % MEM_SIZE] = (value >> 16);
	vm->memory[(adress + 0) % MEM_SIZE] = (value >> 24);
	vm->mem_color[adress % MEM_SIZE] = process->color + 1;
	vm->mem_color[(adress + 1) % MEM_SIZE] = process->color + 1;
	vm->mem_color[(adress + 2) % MEM_SIZE] = process->color + 1;
	vm->mem_color[(adress + 3) % MEM_SIZE] = process->color + 1;
	if (vm->ncurses)
		ft_graphic_handle(vm, adress);
}
