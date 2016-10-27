/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 16:28:26 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/16 09:43:45 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static char	*ft_check_champ_nb(t_vm *vm, int nb_champ, int do_count_live)
{
	t_list		*champions;
	t_process	*champ;

	champions = vm->champions;
	while (champions)
	{
		champ = champions->content;
		if (nb_champ == champ->id_champ)
		{
			if (do_count_live)
				champ->nb_live++;
			return (champ->header.prog_name);
		}
		champions = champions->next;
	}
	return (NULL);
}

void		ft_live(t_vm *vm, t_process *process)
{
	char	*champ_name;

	ft_verbose(vm, process);
	process->cycles_wo_live = 0;
	vm->live++;
	ft_check_champ_nb(vm, process->param[0], 1);
	if ((champ_name = ft_check_champ_nb(vm, process->param[0], 0)))
	{
		vm->last_live = process->param[0];
		if (vm->verbose)
			ft_printf("\nPlayer %d (%s) is said to be alive",
				ft_abs(process->param[0]), champ_name);
	}
	ft_verbose2(process, vm);
}
