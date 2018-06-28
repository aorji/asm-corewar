/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:55:47 by nrepak            #+#    #+#             */
/*   Updated: 2018/06/26 10:55:48 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define 		USAGE 			"Usage: ./asm file_name[0-N][.s] "
# define		USAGE1			"Can't read source file "						 
# define		LEX_ERROR		"Lexical error at ["
# define		SYNT_ERROR		"Syntax error: "
# define		NAME 			"no name in the "
# define		COMMENT 		"no comment in the "
# define		NAME1 			"not the correct quantity of \"name\" in the "
# define		COMMENT1		"not the correct quantity of \"comment\" in the "
# define		USAGE_ERROR		-1
# define		REG_NUMBER		16
# include "./libft/libft.h"

typedef struct s_name_comm
{
	int			name;
	int			comment;
	int			count;
	int			fd;
	int			row;
	int			column;
	int			i;
}				t_name_comm;


int	file_check(int fd, t_name_comm *info, char *f_name);

/*
** -------------------------- Error ----------------------------
*/

int lexical_error(t_name_comm info, char *f_name);
int syntax_error(char *str, char *err, char *f_name);
int	usage_error(char *str, char *name);

/*
** -------------------------- Name/Comment Error ----------------------------
*/

int	name_comm_error(char *line, t_name_comm *info);

#endif
