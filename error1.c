/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 22:08:23 by aorji             #+#    #+#             */
/*   Updated: 2018/07/14 22:08:43 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_uerror(char *f_name)
{
	write(2, "\" ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
}

int			unknown_error(t_name_comm info, char *line, char *f_name)
{
	int		d;
	char	*str;
	int		i;

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
	ft_strdel(&str);
	write_uerror(f_name);
	return (ERROR);
}

int			trash_error(t_name_comm info, char *line, int len, char *f_name)
{
	int		d;
	char	*str;

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
	ft_strdel(&str);
	write(2, "\" ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int			name_lenth_error(void)
{
	write(2, NAME_ERROR, 39);
	write(2, "\n", 1);
	return (ERROR);
}

int			comment_lenth_error(void)
{
	write(2, COMM_ERROR, 43);
	write(2, "\n", 1);
	return (ERROR);
}
