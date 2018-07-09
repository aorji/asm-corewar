/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 14:40:29 by aorji             #+#    #+#             */
/*   Updated: 2018/07/09 14:40:30 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// static int find_label(t_data *data, char *name)
// {
// 	while (data)
// 	{
// 		if (data->label && !ft_strcmp(data->label, name))
// 			return (data->n);
// 		data = data->next;
// 	}
// 	return (-1);
// }

static	void ft_put_fd(char *str, int fd)
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

static	void	bot_name_comm(int fd, char *name, int size)
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

static	void	print_bot_size(int size, int fd)
{
	int n;
	char *str;

	str = ft_itoa_base(size, 16);
	n = ft_strlen(str);
	n = 8 - n;
	while (n)
	{
		ft_put_fd("0", fd);
		n--;
	}
	ft_put_fd(str, fd);
	ft_strdel(&str);
}

static void push_data(int fd, t_name_comm *info, int size)
{
	char *str;

//magic
	str = ft_itoa_base(15369203, 16);
	ft_put_fd("00", fd);
	ft_put_fd(str, fd);
	ft_strdel(&str);
//bot_name
	bot_name_comm(fd, info->name_comm.name, 256);
//NULL
	ft_put_fd("00000000", fd);
//bot_size
	print_bot_size(size, fd);
// bot_com
	bot_name_comm(fd, info->name_comm.comment, 4096);
//NULL
	ft_put_fd("00000000", fd);
//op
	str = ft_itoa_base(info->data->op, 16);
	if (ft_strlen(str) == 1)
		ft_put_fd("0", fd);
	ft_put_fd(str, fd);
	ft_strdel(&str);
}


void	compiler(t_name_comm *info, char *name)
{
	int size;
	int fd;
	char *tmp;

	size = bot_size(info);
	tmp = ft_strjoin(name, ".cor");
	fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	ft_strdel(&tmp);
	push_data(fd, info, size);
}
