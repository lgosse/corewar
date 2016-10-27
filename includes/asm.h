/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaragoz <akaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 13:08:46 by akaragoz          #+#    #+#             */
/*   Updated: 2016/09/19 15:15:56 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <corewar.h>

/*
**	4 bytes : magic number
**	128 bytes : NAME
**	4 bytes = 0
**	4 bytes : prog_size
**	2048 bytes : comment
**	4 bytes = 0
**	prog_size bytes : prog
*/

typedef struct	s_label
{
	char		*label;
	int			addr;
}				t_label;

typedef struct	s_labdir
{
	char		*label;
	int			instr_addr;
	int			addr;
}				t_labdir;

typedef struct	s_inst
{
	char		*ins;
	int			i_instr;
	int			nb_instr;
	int			ocp;
	int			param[3];
	int			ins_octet;
	int			octet;
}				t_inst;

typedef struct	s_asm
{
	t_list		*labels;
	t_list		*labdirs;
	char		*f_content;
	char		prog_name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	int			idx;
	int			fd;
	int			prog_size;
}				t_asm;

int				asm_parse_header(t_asm *asmb);
int				asm_parse_body(t_asm *asmb);
int				ft_get_param_end(char *f_content, int i);
int				ft_parse_params(t_list *labels, char *f_content, int i,
								int idx);
int				ft_jump_nextline(char *str, int i);
int				ft_check_body(t_list *labels, char *f_content, int i);
int				ft_get_instr_len(char *f_content);
int				ft_is_label(char *f_content, int i);
int				asm_finalize(char *path, t_asm *asmb, int i);
void			ft_print_magic(int fd);
void			ft_print_header(t_asm *asmb);
void			ft_print_body(t_asm *asmb, char *f_content, int i);
void			ft_print_param(t_asm *asmb, t_inst *ins);
void			ft_complete_file(t_asm *asmb);
int				ft_strccpy(char *dst, char *src, char c);
int				ft_get_reg(t_inst *ins);
int				ft_get_ind(t_asm *asmb, t_inst *ins, int oc);
int				get_ocp_return(t_inst *ins, int oc);
int				ft_jump_nextline(char *str, int i);
long			ft_atoi_oflow(char *str);

#endif
