/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 13:17:44 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/15 19:23:25 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void		ft_parse_process_get_prog(t_process **process, int fd)
{
	char	verif_end[1];

	ft_bzero((*process)->prog, CHAMP_MAX_SIZE);
	if (read(fd, (*process)->prog, (*process)->header.prog_size + 4) !=
		(*process)->header.prog_size || read(fd, verif_end, 1) != 0)
	{
		free(*process);
		ft_exit_msg("INVALID FORMAT (ERROR 0x03 PROG_SIZE DOES NOT MATCH)");
	}
}

static void		ft_parse_process_prog_size(t_process **process, int fd)
{
	unsigned int	prog_size;
	unsigned char	current_byte;

	read(fd, &current_byte, 1);
	prog_size = current_byte << 24;
	read(fd, &current_byte, 1);
	prog_size += current_byte << 16;
	read(fd, &current_byte, 1);
	prog_size += current_byte << 8;
	read(fd, &current_byte, 1);
	prog_size += current_byte;
	if (prog_size > CHAMP_MAX_SIZE)
	{
		free((*process));
		ft_exit_msg("INVALID FORMAT (ERROR 0x03 PROG_SIZE)");
	}
	(*process)->header.prog_size = prog_size;
}

static void		ft_parse_process_part_two(t_process **process, int fd)
{
	if (read(fd, (*process)->header.prog_name, 128) != 128)
	{
		free(*process);
		ft_exit_msg("INVALID FORMAT (ERROR 0x02 NAME)");
	}
	lseek(fd, 4, SEEK_CUR);
	ft_parse_process_prog_size(process, fd);
	if (read(fd, (*process)->header.comment, 2048) != 2048)
	{
		free(*process);
		ft_exit_msg("INVALID FORMAT (ERROR 0x04 COMMENT)");
	}
	lseek(fd, 4, SEEK_CUR);
}

static void		ft_parse_process_magic_number(t_process **process, int fd,
	char *cor_file_name)
{
	unsigned int	magic;
	unsigned char	current_byte;

	if (read(fd, &current_byte, 1) == -1)
		ft_exit_msg(ft_sprintf("Can't read source file %s", cor_file_name));
	magic = current_byte << 24;
	read(fd, &current_byte, 1);
	magic += current_byte << 16;
	read(fd, &current_byte, 1);
	magic += current_byte << 8;
	read(fd, &current_byte, 1);
	magic += current_byte;
	if (magic != COREWAR_EXEC_MAGIC)
	{
		free((*process));
		ft_exit_msg("INVALID FORMAT (ERROR 0x01 MAGIC NUMBER)");
	}
	(*process)->header.magic = magic;
}

t_process		*ft_parse_process(char *cor_file_name, int nb_next_process,
									t_vm *vm, int i)
{
	int			fd;
	t_process	*process;
	static int	nb_champ;

	if ((process = (t_process *)malloc(sizeof(t_process))))
	{
		if ((fd = open(cor_file_name, O_RDONLY)) != -1)
		{
			process->reg[0] = ft_get_champ_nb(nb_next_process, vm->processes);
			ft_init_process(process);
			process->color = nb_champ;
			process->id = nb_champ++;
			while (++i < 16)
				process->reg[i] = 0;
			ft_parse_process_magic_number(&process, fd, cor_file_name);
			ft_parse_process_part_two(&process, fd);
			ft_parse_process_get_prog(&process, fd);
			process->instruction = -1;
		}
		else
			ft_exit_msg(ft_sprintf("Can't read source file %s", cor_file_name));
	}
	else
		ft_exit_malloc_error();
	return (process);
}
