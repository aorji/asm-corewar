# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrepak <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/26 10:48:56 by nrepak            #+#    #+#              #
#    Updated: 2018/06/26 22:25:16 by aorji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	file_check.c dot.c st.c xor_and_or.c \
			live_zjmp_fork_lfork.c add_sub.c ldi_lldi.c \
			dot_auxiliary.c aff.c sti.c auxiliary.c free.c \
			validation.c  main.c output.c add_data.c co_op.c compiler.c \
			bot_size.c arg.c comp_auxiliary.c flag_struct.c add_label.c \
			check_label.c label.c lexical_syntax_error.c error.c\
			error1.c t_reg.c t_int.c t_dir.c ld_lld.c 

CH_SRCS	=	checker.c

NAME	=	asm
CH_NAME	=	checker

OBJ		=	$(SRCS:.c=.o)
CH_OBJ	=	$(CH_SRCS:.c=.o)

LIB		=	libftprintf.a

FLAGS	=	-Wall -Wextra -Werror

HEADER	=	./asm.h

all: $(NAME) $(CH_NAME)

$(NAME): $(OBJ) 
	@ cd ./libft && make && mv $(LIB) ..
	@ gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

$(CH_NAME): $(CH_OBJ) 
	@ gcc $(FLAGS) $(CH_OBJ) $(LIB) -o $(CH_NAME)

%.o: %.c $(HEADER)
	@ gcc $(FLAGS) -c $<

clean:
	@ /bin/rm -rf $(OBJ)
	@ /bin/rm -rf $(CH_OBJ)
	@ cd ./libft && make clean

fclean: clean
	@ /bin/rm -f $(NAME)
	@ /bin/rm -f $(CH_NAME)
	@ /bin/rm -f $(LIB)
	@ /bin/rm -f libft/$(LIB)
	@ cd ./libft && make fclean

re: fclean all
