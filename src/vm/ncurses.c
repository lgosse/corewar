/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 10:22:17 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/14 17:55:20 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ft_print_octet_highlight(t_vm *vm, int adress)
{
	if (vm->mem_color[adress] >= 0)
		attron(COLOR_PAIR(vm->mem_color[(adress) % MEM_SIZE] + 5));
	else
		attron(COLOR_PAIR(10));
	mvwprintw(stdscr, ((adress) % MEM_SIZE) / 64 + 2,
		((adress) % MEM_SIZE) % 64 * 3 + 3, "%.2x",
		vm->memory[(adress) % MEM_SIZE]);
	if (vm->mem_color[(adress) % MEM_SIZE] >= 0)
		attroff(COLOR_PAIR(vm->mem_color[(adress) % MEM_SIZE] + 5));
	else
		attroff(COLOR_PAIR(10));
}

void		ft_print_octet(t_vm *vm, int adress)
{
	if (vm->mem_color[adress] >= 0)
		attron(COLOR_PAIR(vm->mem_color[(adress) % MEM_SIZE]));
	else
		attron(COLOR_PAIR(5));
	mvwprintw(stdscr, ((adress) % MEM_SIZE) / 64 + 2,
		((adress) % MEM_SIZE) % 64 * 3 + 3, "%.2x",
		vm->memory[(adress) % MEM_SIZE]);
	if (vm->mem_color[(adress) % MEM_SIZE] >= 0)
		attroff(COLOR_PAIR(vm->mem_color[(adress) % MEM_SIZE]));
	else
		attroff(COLOR_PAIR(5));
}

void		ft_print_pc(t_vm *vm, t_process *process)
{
	int adress;

	adress = process->pc2 % MEM_SIZE;
	while (adress < 0)
		adress += MEM_SIZE;
	ft_print_octet_highlight(vm, adress);
	adress = process->pc % MEM_SIZE;
	while (adress < 0)
		adress += MEM_SIZE;
	ft_print_octet(vm, adress);
}

static void	ft_print_vm(t_vm *vm)
{
	int		idx;
	int		line;

	idx = -1;
	line = 0;
	while (++idx < MEM_SIZE)
	{
		if (idx % 64 == 0)
			line++;
		if (vm->mem_color[idx] >= 0)
			attron(COLOR_PAIR(vm->mem_color[idx]));
		else
			attron(COLOR_PAIR(5));
		mvwprintw(stdscr, line + 1, idx % 64 * 3 + 3, "%.2x ", vm->memory[idx]);
		if (vm->mem_color[idx] >= 0)
			attroff(COLOR_PAIR(vm->mem_color[idx]));
		else
			attroff(COLOR_PAIR(5));
	}
}

void		ft_init_visu(t_vm *vm)
{
	int		idx;

	idx = -1;
	(void)vm;
	while (++idx < 255)
		mvprintw(0, idx, "*");
	idx = 0;
	while (++idx < 67)
	{
		mvprintw(idx, 0, "*");
		mvprintw(idx, 197, "*");
		mvprintw(idx, 254, "*");
	}
	idx = -1;
	while (++idx < 255)
		mvprintw(67, idx, "*");
	ft_init_infos(vm);
	ft_print_vm(vm);
	refresh();
	read(0, NULL, 1);
}
