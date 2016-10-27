# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 16:47:05 by lgosse            #+#    #+#              #
#    Updated: 2016/09/21 12:44:26 by gbuclin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM_NAME		=	corewar

ASM_NAME	=	asm

SRC_ASM		=	asm.c \
				asm_check_param.c \
				asm_check_body.c \
				asm_parse_body.c \
				asm_parse_header.c \
				asm_finalize.c \
				asm_print_file.c \
				asm_print_body.c \
				asm_get_param.c \
				asm_complete_file.c \
				ft_atoi_oflow.c \
				ft_strccpy.c \
				ft_jump_next_line.c \
				op.c

SRC_VM		=	op.c \
				vm.c \
				vm_parse_process.c \
				debug_vm.c \
				vm_treat_args.c \
				prepare_memory.c \
				vm_launch.c \
				vm_handle_process.c \
				vm_handle_process2.c \
				vm_virtual_foam_bat.c \
				vm_check_champ.c \
				killemall.c \
				load.c \
				store.c \
				init_vm.c \
				ncurses.c \
				ncurses2.c \
				ncurses3.c

SRC_INSTR	=	add.c \
				aff.c \
				and.c \
				fork.c \
				ld.c \
				ldi.c \
				lfork.c \
				live.c \
				lld.c \
				lldi.c \
				or.c \
				st.c \
				sti.c \
				sub.c \
				xor.c \
				zjmp.c \
				verbose.c \
				verbose2.c \
				adv_invalid.c

OBJ_ASM_NAME	=	$(SRC_ASM:.c=.o)

OBJ_VM_NAME		=	$(SRC_VM:.c=.o)

OBJ_INSTR_NAME	=	$(SRC_INSTR:.c=.o)

SRC_ASM_PATH	=	src/asm/
SRC_VM_PATH		=	src/vm/
SRC_INSTR_PATH	=	src/vm/instructions/
LIB_PATH		=	libft/includes/
OBJ_PATH		=	obj/

SRC_ASM_LIB		=	$(addprefix $(SRC_ASM_PATH),$(SRC_ASM))
SRC_VM_LIB		=	$(addprefix $(SRC_VM_PATH),$(SRC_VM))
SRC_INSTR_LIB	=	$(addprefix $(SRC_INSTR_PATH),$(SRC_INSTR))
OBJ_ASM			=	$(addprefix $(OBJ_PATH),$(OBJ_ASM_NAME))
OBJ_VM			=	$(addprefix $(OBJ_PATH),$(OBJ_VM_NAME))
OBJ_INSTR		=	$(addprefix $(OBJ_PATH),$(OBJ_INSTR_NAME))
LIB				=	$(addprefix -I,$(LIB_PATH))

CC			=	gcc
CFLAGS		=	-Iincludes -Wall -Wextra -Werror
LDFLAGS		=	-Llibft -lft -lncurses
LDLIBS		=	-lft

all:				$(VM_NAME) $(ASM_NAME)

$(ASM_NAME):		$(OBJ_ASM)
	@make -C libft/ -j 8
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "\033[32mCompilation done !\033[0m"

$(VM_NAME):			$(OBJ_VM) $(OBJ_INSTR)
	@make -C libft/ -j 8
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "\033[32mCompilation done !\033[0m"

$(OBJ_PATH)%.o:		$(SRC_ASM_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(LIB) -o $@ -c $<

$(OBJ_PATH)%.o:		$(SRC_VM_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(LIB) -o $@ -c $<

$(OBJ_PATH)%.o:		$(SRC_INSTR_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(LIB) -o $@ -c $<

clean:
	@make -C libft/ fclean > /dev/null
	@rm -fv $(OBJ_ASM) $(OBJ_VM) $(OBJ_INSTR) > /dev/null
	@rm -rfv $(OBJ_PATH) > /dev/null
	@echo "\033[32mObjects cleaned !\033[0m"

fclean:				clean
	@rm -fv $(ASM_NAME) $(VM_NAME) > /dev/null
	@echo "\033[32mExecutable cleaned !\033[0m"

re:					fclean all

.PHONY: all, clean, fclean, re
