/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 17:04:30 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/17 17:52:29 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <libft.h>
# include <op.h>

/*
** header = define in op.h
** id = champion's id
** cycle_bf_exe = number of cycles needed for the process
*/

typedef struct		s_process
{
	t_header		header;
	int				color;
	int				id;
	int				id_champ;
	int				reg[REG_NUMBER];
	int				pc;
	int				pc2;
	int				carry;
	int				cycle_bf_exe;
	int				cycles_wo_live;
	int				param[3];
	t_arg_type		param_type[3];
	char			instruction;
	int				ocp;
	unsigned char	prog[CHAMP_MAX_SIZE];
	int				nb_live;
}					t_process;

#endif
