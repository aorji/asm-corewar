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
# define 		ASM_H
# define 		USAGE 			"Usage: ./asm file_name[0-N][.s] "
# define		USAGE1			"Can't read source file "						 
# define		LEX_ERROR		"Lexical error at ["
# define		SYNT_ERROR		"Syntax error: "
# define		NO_QUAT_ERROR	"You have no close quatation "
# define		NAME_COMM		"not the correct quantity of \"name/comment\" in the "
# define		ERROR			-1
# define		REG_NUMBER		16
# include "./libft/libft.h"

typedef struct s_name_comm
{
	int			name;
	int			comment;
	int			count;
	int			fd;
	int			row;
	int			index;
}				t_name_comm;

/*
** -------------------------- Validation ----------------------------
*/

int				file_check(t_name_comm *info, char *f_name);

/*
** -------------------------- Errors ----------------------------
*/

int 			lexical_error(t_name_comm info, char *f_name);
int 			lexical_error_q(int i, char *f_name);
int 			syntax_error(char *str, char *f_name);
int				usage_error(char *str, char *name);

/*
** -------------------------- Name/Comment Error ----------------------------
*/

int 			dot_check(char *line, char *f_name, t_name_comm *info);

#endif
