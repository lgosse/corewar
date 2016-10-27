/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_treat_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 13:36:38 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/21 12:54:28 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	ft_init_param(t_process *process)
{
	int		i;

	i = -1;
	while (++i < 3)
		process->param[i] = 0;
	i = -1;
	while (++i < 3)
		process->param_type[i] = 0;
}

int			ft_get_champ_nb(int nb_next_process, t_list *processes)
{
	t_list		*begin_list;
	t_process	*current_process;
	int			nb;
	int			ok;

	nb = -1;
	begin_list = processes;
	if (nb_next_process == -1)
		while (1)
		{
			ok = 1;
			processes = begin_list;
			while (processes)
			{
				current_process = processes->content;
				if (current_process->reg[0] == nb)
					ok = 0;
				processes = processes->next;
			}
			if (ok == 1)
				return (nb);
			nb--;
		}
	return (nb_next_process);
}

static void	ft_get_process(t_list **processes, char *arg, int nb_next_process,
							t_vm *vm)
{
	t_list			*current;
	t_list			*champ;

	if ((current = (t_list *)malloc(sizeof(t_list))) &&
		(champ = (t_list *)malloc(sizeof(t_list))) &&
		(champ->content = (t_process *)malloc(sizeof(t_process))))
	{
		if ((current->content = ft_parse_process(arg, nb_next_process, vm, 0)))
		{
			ft_memcpy(champ->content, current->content, sizeof(t_process));
			champ->next = NULL;
			current->content_size = sizeof(t_process);
			((t_process *)(current->content))->cycles_wo_live = 0;
			ft_init_param(current->content);
			current->next = NULL;
			ft_lstadd(&vm->champions, champ);
			ft_lstadd(processes, current);
		}
	}
	else
		ft_exit_malloc_error();
}

int			ft_get_opt(t_vm *vm, char *av, int nb_next_process)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (av[i] == 'a')
			vm->aff = 1;
		else if (av[i] == 'v')
			vm->verbose = 1;
		else if (av[i] == 'c')
			vm->ncurses = 1;
		else if (av[i] == 'G')
			vm->color = 1;
		else
			ft_get_process(&vm->processes, av, nb_next_process, vm);
	}
	return (-1);
}

int			ft_treat_args(int ac, char **av, t_vm *vm)
{
	int				i;
	int				nb_next_process;

	i = 0;
	nb_next_process = -1;
	while (++i < ac && vm->nb_champ <= 4)
		if (!ft_strcmp(av[i], "-dump") && i++ && ft_strisint(av[i]))
			vm->dump = ft_atoi(av[i]);
		else if (!ft_strcmp(av[i], "-n") && i++ && ft_strisint(av[i]))
			nb_next_process = ft_atoi(av[i]);
		else if (av[i][0] == '-')
			nb_next_process = ft_get_opt(vm, av[i], nb_next_process);
		else if (vm->nb_champ++ || 1)
		{
			ft_get_process(&vm->processes, av[i], nb_next_process, vm);
			nb_next_process = -1;
		}
	ft_last_check_champ(vm);
	return (1);
}
