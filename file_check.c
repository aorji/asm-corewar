/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:33:42 by nrepak            #+#    #+#             */
/*   Updated: 2018/06/26 19:33:44 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void white_spaces(char **line, int *column)
{
	while (**line == ' ' || **line == '\t')
	{
		if (**line == '\t')
			*column += 3;
		(*column)++;
		(*line)++;
	}
}

int file_check(int fd, t_name_comm *info, char *f_name)
{
	char *line;

	while (++info->row && (get_next_line(fd, &line) == 1))
	{
		info->column = 0;
		info->i = 0;
		white_spaces(&line, &(info->column));
		if (!name_comm_error(line, info))
			return (lexical_error(*info, f_name));
		//next type of error
	}
	if (!(info->name))
		return (syntax_error(SYNT_ERROR, NAME, f_name));
	else if (!(info->comment))
		return (syntax_error(SYNT_ERROR, COMMENT, f_name));
	if (info->count != 2)
	{
		if ((info->name) != 1)
			return (syntax_error(SYNT_ERROR, NAME1, f_name));
		return (syntax_error(SYNT_ERROR, COMMENT1, f_name));
	}
	return (1);
}
