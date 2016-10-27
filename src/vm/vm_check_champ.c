/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 12:43:51 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/21 12:44:15 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			ft_check_champ_numb(t_vm *vm)
{
	t_list	*champs;
	char	check[vm->nb_champ];
	int		i;
	int		j;

	i = -1;
	while (++i < vm->nb_champ)
		check[i] = 0;
	champs = vm->champions;
	i = 0;
	while (champs)
	{
		check[i] = ((t_process*)(champs->content))->id_champ;
		champs = champs->next;
		i++;
	}
	i = -1;
	while (++i < vm->nb_champ)
	{
		j = -1;
		while (++j < vm->nb_champ)
			if (j != i && check[i] == check[j])
				return (1);
	}
	return (0);
}

void		ft_last_check_champ(t_vm *vm)
{
	if (vm->nb_champ > 4)
		ft_exit_msg("Too many champions");
	if (ft_check_champ_numb(vm))
		ft_exit_msg("Two champions with the same number");
}
