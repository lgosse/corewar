/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 09:25:14 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/16 09:45:36 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ft_apply_ch(t_vm *vm, int ch)
{
	if (ch == -1)
		return ;
	if (ch == KEY_DOWN && vm->sleep - 100 > 0)
		vm->sleep += vm->sleep / 100;
	else if (ch == KEY_UP)
		vm->sleep -= vm->sleep / 100;
	else if (ch == KEY_RIGHT && vm->sleep - 1000 > 0)
		vm->sleep -= vm->sleep / 10;
	else if (ch == KEY_LEFT)
		vm->sleep += vm->sleep / 10;
	else if (ch == 32)
	{
		timeout(-1);
		mvprintw(65, 220, "* PAUSED *");
		while (wgetch(stdscr) != 32)
			;
		timeout(1);
		mvprintw(65, 220, "          ");
	}
}

void		ft_print_champs_lives(t_list *champ, int line)
{
	t_process	*process;

	process = champ->content;
	if (champ->next)
		ft_print_champs_lives(champ->next, line - 4);
	mvwprintw(stdscr, 11 + line, 230, "%d               ", process->nb_live);
	champ = champ->next;
}
