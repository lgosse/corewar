/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_vm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 13:56:57 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/21 13:03:17 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		deb_print_process(t_list *processes)
{
	unsigned int	i;
	t_process		*process;

	while (processes)
	{
		process = processes->content;
		ft_printf("magic : %#x\nprogname : %s\nprog_size : %#x\ncomment : %s\n",
			process->header.magic, process->header.prog_name,
			process->header.prog_size, process->header.comment);
		ft_printf("nb : %d\nid : %d\n", process->reg[0], process->id);
		ft_printf("prog :\n");
		i = 0;
		while (i < process->header.prog_size)
		{
			if (i % 16 == 0 && i != 0)
				ft_printf("\n");
			else if (i % 8 == 0 && i != 0)
				ft_printf(" ");
			ft_printf("%.2x ", (unsigned char)(process->prog[i]));
			i++;
		}
		ft_putchar('\n');
		processes = processes->next;
	}
}

void		deb_print_memory(t_vm *vm)
{
	int		i;
	int		offset;

	i = -1;
	offset = 0;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			offset == 0 ? ft_printf("0x%#.4x : ", offset) :
				ft_printf("\n%#.4x : ", offset);
			offset += 64;
		}
		if (vm->color && vm->mem_color[i] == 0)
			ft_printf("%[g,B]T%.2x %[0]T", (unsigned char)vm->memory[i]);
		else if (vm->color && vm->mem_color[i] == 1)
			ft_printf("%[b,B]T%.2x %[0]T", (unsigned char)vm->memory[i]);
		else if (vm->color && vm->mem_color[i] == 2)
			ft_printf("%[r,B]T%.2x %[0]T", (unsigned char)vm->memory[i]);
		else if (vm->color && vm->mem_color[i] == 3)
			ft_printf("%[c,B]T%.2x %[0]T", (unsigned char)vm->memory[i]);
		else
			ft_printf("%.2x ", (unsigned char)vm->memory[i]);
	}
	ft_printf("\n");
}
