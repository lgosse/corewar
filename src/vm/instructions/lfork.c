/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuclin <gbuclin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 16:32:07 by gbuclin           #+#    #+#             */
/*   Updated: 2016/09/10 12:28:45 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	ft_copy_reg(t_process *new_process, t_process *process)
{
	int		i;

	i = -1;
	while (++i < 16)
		new_process->reg[i] = process->reg[i];
	i = -1;
	while (++i < 3)
		new_process->param[i] = 0;
	i = -1;
	while (++i < 3)
		new_process->param_type[i] = 0;
}

static void	ft_lfork2(t_vm *vm, t_process *process, t_process *new_process,
	t_list *lst)
{
	new_process->carry = process->carry;
	new_process->cycle_bf_exe = 0;
	new_process->instruction = -1;
	new_process->cycles_wo_live = process->cycles_wo_live;
	new_process->color = process->color;
	lst->content = new_process;
	lst->next = NULL;
	lst->content_size = sizeof(t_list);
	ft_lstadd(&vm->processes, lst);
	ft_verbose2(process, vm);
}

void		ft_lfork(t_vm *vm, t_process *process)
{
	t_list		*lst;
	t_process	*new_process;

	lst = NULL;
	ft_verbose(vm, process);
	if (vm->verbose)
		ft_printf(" (%d)",
			(process->pc + (short)process->param[0]));
	if (((new_process = (t_process*)malloc(sizeof(t_process))) == NULL) ||
		((lst = (t_list *)malloc(sizeof(t_list))) == NULL))
		ft_exit_malloc_error();
	ft_copy_reg(new_process, process);
	new_process->header = process->header;
	new_process->id = vm->nb_process++;
	new_process->id_champ = process->id_champ;
	new_process->pc =
		(short)(process->pc + (short)process->param[0]) % MEM_SIZE;
	if (new_process->pc < 0)
		new_process->pc += MEM_SIZE;
	ft_lfork2(vm, process, new_process, lst);
}
