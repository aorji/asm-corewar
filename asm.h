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
# define		TRASH_ERROR 	"Syntax error at token [TOKEN]["
# define		NO_QUAT_ERROR	"You have no close quatation "
# define		NAME_COMM		"not the correct quantity of \"name/comment\" in the "
# define		ST1_ERROR		"Invalid parameter 1 type for instruction \"st\"\n"
# define		ST2_ERROR		"Invalid parameter 2 type for instruction \"st\"\n"
# define		SEP_ERROR		"Punctuation error: no comma at ["
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
	int 		tab;
	t_list		*label;
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
int				trash_error(t_name_comm info, char *line, int tr);
char			*sep_error(t_name_comm *info);
char			*st_error(int i);

/*
** --------------------------  Error ----------------------------
*/

int 			dot_check(char *line, char *f_name, t_name_comm *info);
int				st_check(char *line, t_name_comm *info, char *f_name);

/*
** -------------------------- Auxliary ----------------------------
*/

char*			ws(char *line, t_name_comm *info);
int				trash(char *line, int i);
void			add_tab(t_name_comm *info);

#endif
