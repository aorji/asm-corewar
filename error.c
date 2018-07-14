/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 11:57:00 by aorji             #+#    #+#             */
/*   Updated: 2018/06/28 11:57:02 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int lexical_error(t_name_comm info, char *f_name)
{
	write(2, LEX_ERROR, 18);
	ft_putnbr(info.row);
	write(2, ":", 1);
	ft_putnbr(info.index + 1 + info.tab);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int lexical_error_q(int i, char *f_name)
{
	write(2, NO_QUAT_ERROR, 28);
	if (i)
		write(2, "for \"name\" in the \"", 20);
	else
		write(2, "for \"comment\" in the \"", 22);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int syntax_error(char *str, char *f_name)
{
	write(2, str, ft_strlen(str));
	write(2, NAME_COMM, ft_strlen(NAME_COMM));
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int	usage_error(char *str, char *f_name)
{
	write (2, str, ft_strlen(str));
	if (f_name)
	{
		write(2, "\"", 1);
		write (2, f_name, ft_strlen(f_name));
		write(2, "\"", 1);
	}
	write(2, "\n", 1);
	return (ERROR);
}

int	trash_error(t_name_comm info, char *line, int len, char *f_name)
{
	int d;
	char *str;

	write(2, TRASH_ERROR, 30);
	d = 3 - ft_number_size(info.row);
	while (d--)
		ft_putnbr(0);
	ft_putnbr(info.row);
	write(2, ":", 1);
	d = 3 - ft_number_size(info.index + 1 + info.tab);
	while (d--)
		ft_putnbr(0);
	ft_putnbr(info.index + 1 + info.tab);
	write(2, "] INSTRUCTION \"", 16);
	str = ft_strsub(line, len, ft_strlen(line) - len);
	write(2, str, ft_strlen(line) - len);
	free(str);
	str = NULL;
	write(2, "\" ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int	unknown_error(t_name_comm info, char *line, char *f_name)
{
	int d;
	char *str;
	int i;

	i = 0;
	if (line[0] == COMMENT_CHAR[0] || line[0] == COMMENT_CHAR[1])
		return (0);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	write(2, UN_ERROR, 30);
	d = 3 - ft_number_size(info.row);
	while (d--)
		ft_putnbr(0);
	ft_putnbr(info.row);
	write(2, ":", 1);
	d = 3 - ft_number_size(info.index + 1 + info.tab);
	while (d--)
		ft_putnbr(0);
	ft_putnbr(info.index + 1 + info.tab);
	write(2, "] INSTRUCTION \"", 16);
	str = ft_strsub(line, 0, i);
	write(2, str, i);
	free(str);
	str = NULL;
	write(2, "\" ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

char	*sep_error(t_name_comm *info, char *f_name)
{
	write(2, SEP_ERROR, 32);
	ft_putnbr(info->row);
	write(2, ":", 1);
	ft_putnbr((info->index) + (info->tab) + 1);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (NULL);
}	

char	*instract_error(t_name_comm *info, char *f_name)
{
	write(2, INSTRUCT_ERROR, 19);
	ft_putnbr(info->row);
	write(2, ":", 1);
	ft_putnbr(info->index + 1 + info->tab);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (NULL);
}

int label_error(char *name, int x, int y, char *f_name)
{
	write(2, LABEL_ERROR, 14);
	write(2, "\"", 1);
	write(2, name, ft_strlen(name));
	write(2, "\" [", 3);
	ft_putnbr(x);
	write(2, ":", 1);
	ft_putnbr(y);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int end_error(char *f_name)
{
	write(2, END_ERROR, 84);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int name_lenth_error(void)
{
	write(2, NAME_ERROR, 39);
	write(2, "\n", 1);
	return (ERROR);
}

int comment_lenth_error(void)
{
	write(2, COMM_ERROR, 43);
	write(2, "\n", 1);
	return (ERROR);
}
