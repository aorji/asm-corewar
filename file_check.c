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

static int lexical_error(int row, int column, char *f_name)
{
	write(2, LEX_ERROR, 18);
	ft_putnbr(row);
	write(2, ":", 1);
	ft_putnbr(column);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (-1);
}

static int syntax_error(char *str, char *err, char *f_name)
{
	write(2, str, ft_strlen(str));
	write(2, err, ft_strlen(err));
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (-1);
}

static int name_exist(int *column, char *line, t_name_comm *info)
{
	int i;
	int j;

	j = 0;
	i = 0;
	//open "
	while ((line[i] != ' ' && line[i] != '\t') && line[i])
		i++;
	while ((line[i] == ' ' || line[i] == '\t') && line[i])
		i++;
	j = i;
	(*column) = i + 2;
	if (line[i++] != '\"')
		return (0);
	// 
	while (line[i] != '\"' && line[i])
		i++;
	(*column) = i + 2;
	if (!(line[i]))
		return (0);
	// push to struct
	if (line[0] == 'n')
	{
		info->name = ft_strsub(line, j + 1, i - j - 1);
		// printf("%s\n", info->name);
	}
	else
	{
		info->comment = ft_strsub(line, j + 1, i - j - 1);
		// printf("%s\n", info->comment);
	}
	// 
	return (1);
}

static int	name_comm_error(char *line, int *column, t_name_comm *info)
{
	if (line[0] == '.')
	{
		line++;
		(*column)++;
		if (!ft_strncmp(line, "name", 4) || !ft_strncmp(line, "comment", 7))
			if (name_exist(column, line, info))
			{
				++(info->count);
				return (1);
			}
		return (0);
	}
	return (1);
}

int file_check(int fd, t_name_comm *info, char *f_name)
{
	char *line;
	int row;
	int column;

	row = 0;
	column = 0;
	while (++row && (get_next_line(fd, &line) == 1))
	{
		if (!name_comm_error(line, &column, info))
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
