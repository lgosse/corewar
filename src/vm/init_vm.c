/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 14:08:12 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/21 12:54:40 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ft_init_ncurses(t_vm *vm)
{
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_CYAN);
	init_pair(7, COLOR_WHITE, COLOR_RED);
	init_pair(8, COLOR_WHITE, COLOR_YELLOW);
	init_pair(9, COLOR_WHITE, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	ft_init_visu(vm);
}

void		ft_init_vm(t_vm *vm)
{
	vm->dump = -1;
	vm->processes = NULL;
	vm->champions = NULL;
	vm->nb_champ = 0;
	vm->verbose = 0;
	vm->aff = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->total_cycles = 1;
	vm->cycles = 1;
	vm->live = 0;
	vm->last_live = 0;
	vm->ctd_decrem = 0;
	vm->aff = 0;
	vm->ncurses = 0;
	vm->nb_checks = 0;
	vm->sleep = 10000;
}

void		ft_init_process(t_process *process)
{
	process->id_champ = process->reg[0];
	process->nb_live = 0;
}

void		init_tab_instruction(t_vm *vm)
{
	vm->f[0] = ft_live;
	vm->f[1] = ft_ld;
	vm->f[2] = ft_st;
	vm->f[3] = ft_add;
	vm->f[4] = ft_sub;
	vm->f[5] = ft_and;
	vm->f[6] = ft_or;
	vm->f[7] = ft_xor;
	vm->f[8] = ft_zjmp;
	vm->f[9] = ft_ldi;
	vm->f[10] = ft_sti;
	vm->f[11] = ft_fork;
	vm->f[12] = ft_lld;
	vm->f[13] = ft_lldi;
	vm->f[14] = ft_lfork;
	vm->f[15] = ft_aff;
}
