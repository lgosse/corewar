/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 15:17:30 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/15 19:48:14 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	ft_print_champ_infos(t_list *champ, int line)
{
	t_process	*process;

	process = champ->content;
	if (champ->next)
		ft_print_champ_infos(champ->next, line - 4);
	mvwprintw(stdscr, 9 + line, 202, "Player %d : ", process->id_champ);
	attron(COLOR_PAIR(FT_ABS(process->id_champ)));
	mvwprintw(stdscr, 9 + line, 214, "%s", process->header.prog_name);
	attroff(COLOR_PAIR(FT_ABS(process->id_champ)));
	mvwprintw(stdscr, 10 + line, 204, "\"%.48s...\"", process->header.comment);
	mvprintw(11 + line, 204, "Lives in current period : ");
	champ = champ->next;
}

static void	ft_print_dog(void)
{
	mvprintw(42, 215, "░▄▀▄▀▀▀▀▄▀▄░░░░░░░░░ ");
	mvprintw(43, 215, "░█░░░░░░░░▀▄░░░░░░▄░ ");
	mvprintw(44, 215, "█░░▀░░▀░░░░░▀▄▄░░█░█ ");
	mvprintw(45, 215, "█░▄░█▀░▄░░░░░░░▀▀░░█ ");
	mvprintw(46, 215, "█░░▀▀▀▀░░░░░░░░░░░░█ ");
	mvprintw(47, 215, "█░░░░░░░░░░░░░░░░░░█ ");
	mvprintw(48, 215, "█░░░░░░░░░░░░░░░░░░█ ");
	mvprintw(49, 215, "░█░░▄▄░░▄▄▄▄░░▄▄░░█░ ");
	mvprintw(50, 215, "░█░▄▀█░▄▀░░█░▄▀█░▄▀░ ");
	mvprintw(51, 215, "░░▀░░░▀░░░░░▀░░░▀░░░");
}

void		ft_init_infos(t_vm *vm)
{
	(void)vm;
	mvprintw(3, 220, "* COREWAR *");
	mvprintw(5, 202, "Cycle/Second limit : 100");
	mvprintw(7, 202, "Cycle : 0");
	mvprintw(9, 202, "Processes : ");
	ft_print_champ_infos(vm->processes, vm->nb_champ * 4);
	ft_print_dog();
	mvwprintw(stdscr, 29, 202, "CYCLE_TO_DIE : %d", vm->cycle_to_die);
	mvprintw(31, 202, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(stdscr, 33, 202, "NBR_LIVE : %d", vm->live);
	mvprintw(35, 202, "MAX_CHECKS : %d", MAX_CHECKS);
}

void		ft_refresh_infos(t_vm *vm)
{
	mvwprintw(stdscr, 5, 223, "%d          ", 1000000 / vm->sleep);
	mvwprintw(stdscr, 7, 210, "%d     ", vm->total_cycles);
	mvwprintw(stdscr, 9, 214, "%d      ", vm->nb_process);
	mvwprintw(stdscr, 29, 217, "%d    ", vm->cycle_to_die);
	mvwprintw(stdscr, 33, 213, "%d    ", vm->live);
	ft_print_champs_lives(vm->champions, vm->nb_champ * 4);
	move(0, 0);
}

void		ft_erase_pc(t_vm *vm, t_process *process)
{
	int adress;

	adress = process->pc;
	adress %= MEM_SIZE;
	while (adress < 0)
		adress += MEM_SIZE;
	ft_print_octet(vm, adress);
}
