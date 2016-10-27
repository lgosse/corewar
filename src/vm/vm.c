/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 17:27:05 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/14 15:24:47 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ft_print_winner(t_vm *vm)
{
	t_list		*champions;
	t_process	*champ;

	champions = vm->champions;
	if (vm->last_live == 0)
	{
		champ = champions->content;
		ft_printf("Contestant %d, \"%s\", has won !\n",
			FT_ABS(champ->id_champ), champ->header.prog_name);
		return ;
	}
	while (champions)
	{
		champ = champions->content;
		if (vm->last_live == champ->id_champ)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",
				FT_ABS(champ->id_champ), champ->header.prog_name);
			return ;
		}
		champions = champions->next;
	}
}

static void	ft_introduce_contestants(t_list *champs)
{
	t_process	*act;

	act = champs->content;
	if (champs->next)
		ft_introduce_contestants(champs->next);
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		FT_ABS(act->id_champ), act->header.prog_size, act->header.prog_name,
		act->header.comment);
}

int			main(int ac, char **av)
{
	t_vm	*vm;

	if ((vm = (t_vm *)malloc(sizeof(t_vm))))
	{
		ft_init_vm(vm);
		init_tab_instruction(vm);
		ft_treat_args(ac, av, vm);
		ft_prepare_memory(vm);
		if (vm->ncurses)
			ft_init_ncurses(vm);
		vm->nb_process = vm->nb_champ;
		if (!vm->ncurses)
		{
			ft_printf("Introducing contestants...\n");
			ft_introduce_contestants(vm->processes);
		}
		ft_launch_vm(vm);
	}
	else
		ft_exit_malloc_error();
	if (vm->ncurses)
		endwin();
	ft_print_winner(vm);
	ft_kill_vm(vm);
	return (1);
}
