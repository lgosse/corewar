/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 14:17:46 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/15 19:41:35 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int		ft_check_champs_live(t_vm *vm, t_list *prev, t_list *current_process)
{
	t_process		*process;

	process = current_process->content;
	if (process->cycles_wo_live >= vm->cycle_to_die)
	{
		if (vm->verbose)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				process->id + 1, process->cycles_wo_live, vm->cycle_to_die);
		ft_savage_slaughter(vm, prev, current_process);
		return (1);
	}
	return (0);
}

void	ft_search_for_preys(t_vm *vm)
{
	t_list		*prev;
	t_list		*current_process;
	t_list		*next;

	prev = NULL;
	current_process = vm->processes;
	next = current_process->next;
	while (current_process)
		if (ft_check_champs_live(vm, prev, current_process))
		{
			if (prev)
				prev->next = next;
			current_process = next;
			if (next)
				next = current_process->next;
		}
		else
		{
			prev = current_process;
			current_process = next;
			if (current_process)
				next = current_process->next;
		}
}

void	ft_decrement_cycle_to_die(t_vm *vm)
{
	t_list		*champs;
	t_process	*champ;

	vm->cycle_to_die -= CYCLE_DELTA;
	if (vm->verbose)
		ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
	vm->nb_checks = 0;
	champs = vm->champions;
	while (champs)
	{
		champ = champs->content;
		champ->nb_live = 0;
		champs = champs->next;
	}
}

int		ft_handle_cycles(t_vm *vm)
{
	int		ch;

	vm->total_cycles++;
	vm->cycles++;
	if (vm->ncurses)
	{
		timeout(-1);
		usleep(vm->sleep);
		timeout(0);
		ch = wgetch(stdscr);
		ft_apply_ch(vm, ch);
		ft_refresh_infos(vm);
		refresh();
	}
	if (vm->cycles > vm->cycle_to_die)
	{
		vm->cycles = 1;
		ft_search_for_preys(vm);
		vm->nb_checks++;
		if (vm->live > (NBR_LIVE - 1) || vm->nb_checks == MAX_CHECKS)
			ft_decrement_cycle_to_die(vm);
		vm->live = 0;
	}
	return (1);
}

int		ft_launch_vm(t_vm *vm)
{
	t_list		*current_process;
	t_process	*process;

	while (vm->total_cycles != vm->dump + 1 && vm->processes)
	{
		if (vm->verbose)
			ft_printf("It is now cycle %d\n", vm->total_cycles);
		current_process = vm->processes;
		while (current_process)
		{
			process = current_process->content;
			if (process->pc >= MEM_SIZE)
				process->pc %= MEM_SIZE;
			while (process->pc < 0)
				process->pc += MEM_SIZE;
			process->cycles_wo_live++;
			ft_handle_process(vm, process);
			current_process = current_process->next;
		}
		ft_handle_cycles(vm);
	}
	if (vm->processes)
		deb_print_memory(vm);
	return (1);
}
