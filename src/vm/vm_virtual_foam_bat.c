/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_virtual_foam_bat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 12:24:44 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/16 14:33:21 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_murder_with_foam_bat(t_list **prey)
{
	(void)prey;
	free((*prey)->content);
	(*prey)->content = NULL;
	free(*prey);
	*prey = NULL;
}

void	ft_savage_slaughter(t_vm *vm, t_list *prev_process,
							t_list *current_process)
{
	if (prev_process)
		prev_process->next = current_process->next;
	else
		vm->processes = current_process->next;
	if (vm->ncurses)
		ft_erase_pc(vm, current_process->content);
	ft_murder_with_foam_bat(&current_process);
	if (vm->ncurses)
		ft_putchar('\a');
}
