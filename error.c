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

int	usage_error(char *str, char *name)
{
	write (2, str, ft_strlen(str));
	if (name)
	{
		write(2, "\"", 1);
		write (2, name, ft_strlen(name));
		write(2, "\"", 1);
	}
	write(2, "\n", 1);
	return (ERROR);
}

int	trash_error(t_name_comm info, char *line, int len)
{
	int d;

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
	write(2, ft_strsub(line, len, ft_strlen(line) - len), ft_strlen(line) - len);
	write(2, "\"\n", 2);
	return (ERROR);
}

char	*sep_error(t_name_comm *info)
{
	write(2, SEP_ERROR, 32);
	ft_putnbr(info->row);
	write(2, ":", 1);
	ft_putnbr((info->index) + (info->tab) + 1);
	write(2, "]\n", 2);
	return (NULL);
}	

char	*st_error(int i)
{
	if (i == 1)
		write(2, ST1_ERROR, 46);
	else
		write(2, ST2_ERROR, 46);
	return (NULL);
}



