/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killemall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 17:19:44 by lgosse            #+#    #+#             */
/*   Updated: 2016/08/17 17:24:06 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	ft_kill_champions(t_list *champions)
{
	if (champions)
	{
		if (champions->next)
			ft_kill_champions(champions->next);
		free(champions->content);
		free(champions);
	}
}

static void	ft_kill_processes(t_list *processes)
{
	if (processes)
	{
		if (processes->next)
			ft_kill_processes(processes->next);
		free(processes->content);
		free(processes);
	}
}

void		ft_kill_vm(t_vm *vm)
{
	ft_kill_processes(vm->processes);
	ft_kill_champions(vm->champions);
	free(vm);
}
