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

SRCS	=	main.c file_check.c error.c dot.c st.c t_reg.c t_int.c label.c \
			xor_and_or.c t_dir.c ld_lld.c live_zjmp_fork_lfork.c add_sub.c \
			ldi_lldi.c aff.c sti.c auxliary.c output.c add_data.c co_op.c \
			compiler.c bot_size.c

NAME	=	asm

OBJ		=	$(SRCS:.c=.o)

LIB		=	libft.a

FLAGS	=	-Wall -Wextra -Werror

HEADER	=	./asm.h

all: $(NAME)

$(NAME):$(OBJ)
	@ cd ./libft && make && mv $(LIB) ..
	@ gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c $(HEADER)
	@ gcc $(FLAGS) -c $<

clean:
	@ /bin/rm -rf $(OBJ)
	@ cd ./libft && make clean

fclean: clean
	@ /bin/rm -f $(NAME)
	@ /bin/rm -f $(LIB)
	@ /bin/rm -f libft/$(LIB)
	@ cd ./libft && make fclean

re: fclean all
