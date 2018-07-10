/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_auxiliary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 21:30:52 by aorji             #+#    #+#             */
/*   Updated: 2018/07/10 21:30:54 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void ft_put_fd(char *str, int fd)
{
	int i;
	static int delim;

	i = 0;
	while (str[i])
	{
		++delim;
		ft_putchar_fd(str[i], fd);
		if (delim % 4 == 0)
			ft_putchar_fd(' ', fd);
		if (delim % 32 == 0)
			ft_putchar_fd('\n', fd);
		i++;
	}
}

int n_byte(t_data *data, char *name)
{
	while (data)
	{
		if (data->label && !ft_strcmp(data->label, name))
			return (data->n);
		data = data->next;
	}
	return (-1);
}

void	bot_name_comm(int fd, char *name, int size)
{
	int i = 0;
	char *str;

	while (name[i])
	{
		str = ft_itoa_base(name[i], 16);
		if (ft_strlen(str) == 1)
			ft_put_fd("0", fd);
		ft_put_fd(str, fd);
		ft_strdel(&str);
		i++;
		size -= 2;
	}
	while (size)
	{
		ft_put_fd("0", fd);
		size--;
	}
}

int binary_code(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == 'r')
		return (T_REG);
	if (arg[0] == '%')
		return (T_DIR);
	return (T_IND);
}