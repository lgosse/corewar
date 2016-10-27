/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 13:18:56 by lgosse            #+#    #+#             */
/*   Updated: 2016/09/21 12:53:25 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <corewar.h>
# include <locale.h>
# include <ncurses.h>

/*
** dump = number of cycle before dumping the memory and exiting the program
** live = number of live in the current cycle_to_die loop
** chps_live = binary indicator for champions who said "i'm alive"
** last_live = 0, 1, 2 or 3 default -1
** aff = default : 0 (hide outputs from aff)
** ctd_decrem = default 0, if the ctd is decrease ctd_decrem = 1
** 				when ctd_decrem = 1 the cycles_wo_live of all processes
** 				are reset
*/

typedef struct		s_vm
{
	void			(*f[16])(struct s_vm *, t_process *);
	t_list			*processes;
	t_list			*champions;
	unsigned char	memory[MEM_SIZE];
	char			mem_color[MEM_SIZE];
	int				dump;
	int				verbose;
	int				nb_champ;
	int				nb_process;
	int				cycle_to_die;
	int				ctd_decrem;
	int				total_cycles;
	int				cycles;
	int				nb_checks;
	int				live;
	int				last_live;
	int				aff;
	int				ncurses;
	int				sleep;
	int				color;
}					t_vm;

# define OPCODE_LIVE	1
# define OPCODE_LD		2
# define OPCODE_ST		3
# define OPCODE_ADD		4
# define OPCODE_SUB		5
# define OPCODE_AND		6
# define OPCODE_OR		7
# define OPCODE_XOR		8
# define OPCODE_ZJMP	9
# define OPCODE_LDI		10
# define OPCODE_STI		11
# define OPCODE_FORK	12
# define OPCODE_LLD		13
# define OPCODE_LLDI	14
# define OPCODE_LFORK	15
# define OPCODE_AFF		16

# define OP_TAB			g_op_tab[(int)process->instruction]

t_process			*ft_parse_process(char *cor_file_name, int nb_next_process,
									t_vm *vm, int i);
void				deb_print_process(t_list *processes);
int					ft_treat_args(int ac, char **av, t_vm *vm);
int					ft_get_champ_nb(int nb_next_process, t_list *processes);
void				ft_prepare_memory(t_vm *vm);
void				deb_print_memory(t_vm *vm);
void				ft_lstaddchamp(t_list **processes, t_list *process);
void				ft_virtual_foam_bat(t_vm *vm, int id);
void				ft_handle_process(t_vm *vm, t_process *process);
int					ft_launch_vm(t_vm *vm);
void				ft_savage_slaughter(t_vm *vm, t_list *prev_process,
						t_list *current_process);
void				ft_kill_vm(t_vm *vm);
void				ft_init_vm(t_vm *vm);
void				ft_init_ncurses(t_vm *vm);
void				ft_init_visu(t_vm *vm);
void				init_tab_instruction(t_vm *vm);
int					ft_check_champ_numb(t_vm *vm);
int					ft_check_param(t_process *process, int i);
int					ft_get_ocp(t_vm *vm, t_process *process);
void				ft_get_instruction(t_vm *vm, t_process *process);
void				ft_last_check_champ(t_vm *vm);

/*
** instructions
*/

void				ft_live(t_vm *vm, t_process *process);
void				ft_ld(t_vm *vm, t_process *process);
void				ft_st(t_vm *vm, t_process *process);
void				ft_add(t_vm *vm, t_process *process);
void				ft_sub(t_vm *vm, t_process *process);
void				ft_and(t_vm *vm, t_process *process);
void				ft_or(t_vm *vm, t_process *process);
void				ft_xor(t_vm *vm, t_process *process);
void				ft_zjmp(t_vm *vm, t_process *process);
void				ft_ldi(t_vm *vm, t_process *process);
void				ft_sti(t_vm *vm, t_process *process);
void				ft_fork(t_vm *vm, t_process *process);
void				ft_lld(t_vm *vm, t_process *process);
void				ft_lldi(t_vm *vm, t_process *process);
void				ft_lfork(t_vm *vm, t_process *process);
void				ft_aff(t_vm *vm, t_process *process);
void				ft_print_reg(t_process *process, int i);

/*
** utilities
*/

void				ft_store(t_vm *vm, t_process *process, int adress);
int					ft_load(t_vm *vm, int size, int adress);

/*
** verbose
*/

void				ft_adv_invalid(t_process *process, t_vm *vm);
void				ft_print_ind(t_vm *vm, t_process *process, int i);
void				ft_verbose(t_vm *vm, t_process *process);
void				ft_verbose2(t_process *process, t_vm *vm);
void				ft_verbose3(t_process *process, t_vm *vm);
int					ft_verbose5(t_process *process);
void				ft_print_pc(t_vm *vm, t_process *process);
void				ft_print_octet(t_vm *vm, int adress);
void				ft_erase_pc(t_vm *vm, t_process *process);
void				ft_refresh_infos(t_vm *vm);
void				ft_init_infos(t_vm *vm);
void				ft_apply_ch(t_vm *vm, int ch);
void				ft_init_process(t_process *process);
void				ft_print_champs_lives(t_list *champ, int line);

#endif
