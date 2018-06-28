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

static void white_spaces(char **


	line, int *column)
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
	int row;
	int column;

	row = 0;
	while (++row && (get_next_line(fd, &line) == 1))
	{
		column = 0;
		white_spaces(&line, &column);
		if (!name_comm_error(line, &column, info, &row))
			return (lexical_error(row, column, f_name));
		//next type of error
	}
	if (info->count != 2)
	{
		if (!(info->name))
			return (syntax_error(SYNT_ERROR, NAME, f_name));
		return (syntax_error(SYNT_ERROR, COMMENT, f_name));
	}
	return (1);
}
