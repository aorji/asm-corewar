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
# define		INSTRUCT_ERROR	"Invalid parameter ["
# define		SEP_ERROR		"Punctuation error: no comma at ["
# define		LABEL_ERROR		"No such label "
# define		UN_ERROR		"Invalid instruction at token ["
# define		END_ERROR		"Syntax error - unexpected end of input\
 (Perhaps you forgot to end with a newline?) "
# define		NAME_ERROR		"Champion name too long (Max length 128)"
# define		COMM_ERROR		"Champion comment too long (Max length 2048)"


# define		OUTPUT			"Writing output program to "


# define		ERROR			-1
# define		REG_NUMBER		16


#define			COMMENT_CHAR	'#'
#define			LABEL_CHAR		':'
#define			DIRECT_CHAR		'%'
#define			SEPARATOR_CHAR	','


# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)


# include "./libft/libft.h"

typedef struct  	s_header
{
	char			*name;
	char			*comment;
}					t_header;

typedef struct  	s_file_name
{
	char			*name;
	struct 	s_file_name *next;
}					t_file_name;

typedef struct  	s_label
{
	char			*name;
	int 			found;
	int 			x;
	int 			y;
	struct 	s_label *next;
}					t_label;

typedef struct  	s_data
{
	char			*label;
	char 			*func;
	char 			*arg1;
	char 			*arg2;
	char 			*arg3;
	struct 	s_data 	*next;
}					t_data;

typedef struct		s_name_comm
{
	int				name;
	int				comment;
	int				count;
	int				fd;
	int				row;
	int				index;
	int 			tab;
	int				in;
	t_label			*label;
	t_data			*data;
	t_header		name_comm;
}					t_name_comm;

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
int				usage_error(char *str, char *f_name);
int				trash_error(t_name_comm info, char *line, int tr, char *f_name);
char			*sep_error(t_name_comm *info, char *f_name);
char			*instract_error(t_name_comm *info, char *f_name);
int				label_error(char *name, int x, int y, char *f_name);
int				end_error(char *f_name);
int				unknown_error(t_name_comm info, char *line, char *f_name);
int 			name_lenth_error(void);
int 			comment_lenth_error(void);

/*
** --------------------------  INSTRUCTION ----------------------------
*/

int 			dot(char *line, char *f_name, t_name_comm *info);
int				st(char *line, t_name_comm *info, char *f_name);
int				xor_and_or(char *line, t_name_comm *info, char *f_name);
int				ld_lld(char *line, t_name_comm *info, char *f_name);
int				live_zjmp_fork_lfork(char *line, t_name_comm *info, char *f_name);
int				add_sub(char *line, t_name_comm *info, char *f_name);
int				aff(char *line, t_name_comm *info, char *f_name);
int				sti(char *line, t_name_comm *info, char *f_name);
int				ldi_lldi(char *line, t_name_comm *info, char *f_name);

/*
** -------------------------- Auxliary ----------------------------
*/

char*			ws(char *line, t_name_comm *info);
int				trash(char *line, int i);
void			add_tab(t_name_comm *info);
void			add_data(char *str, int i, t_name_comm *info);

/*
** -------------------------- Label ----------------------------
*/

char 			*label_arg1(char *line, t_name_comm *info, char *f_name);
char 			*label_arg2(char *line, t_name_comm *info, char *f_name);
int				add_label(char *line, t_name_comm *info);
char			*label(char *line, t_name_comm *info, char *f_name, int *j);

/*
** -------------------------- T_REG ----------------------------
*/

char 			*t_reg_arg1(char *line, t_name_comm *info, char *f_name);
char 			*t_reg_arg2(char *line, t_name_comm *info, char *f_name);

/*
** -------------------------- T_DIR ----------------------------
*/

char 			*t_dir_arg1(char *line, t_name_comm *info, char *f_name);
char 			*t_dir_arg2(char *line, t_name_comm *info, char *f_name);

/*
** -------------------------- T_INT ----------------------------
*/

char 			*t_int_arg1(char *line, t_name_comm *info, char *f_name);
char 			*t_int_arg2(char *line, t_name_comm *info, char *f_name);

/*
** -------------------------- Output ----------------------------
*/

int				print(char **av, int ac, t_name_comm info);

#endif
