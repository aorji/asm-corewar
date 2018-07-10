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

static void		print_codage(t_data *data, int fd)
{
	int first;
	int second;
	int third;
	int res;
	char *str;

	if (data->co)
	{
		first = binary_code(data->arg1);
		second = binary_code(data->arg2);
		third = binary_code(data->arg3);
		if (second)
			second >>= 2;
		if (third)
			third >>= 4;
		res = first | second | third; 
		str = ft_itoa_base(res, 16);
		ft_put_fd(str, fd);
		ft_strdel(&str);
	}
}

static void print_to_cor(t_data *data, int fd)
{
	t_data *tmp;
	char *str;

	tmp = data;
	while (tmp)
	{
		//op
		str = ft_itoa_base(tmp->op, 16);
		if (ft_strlen(str) == 1)
			ft_put_fd("0", fd);
		ft_put_fd(str, fd);
		ft_strdel(&str);
		// codage
		print_codage(tmp, fd);
		// each
		choose_type(data, tmp, tmp->arg1, fd);
		choose_type(data, tmp, tmp->arg2, fd);
		choose_type(data, tmp, tmp->arg3, fd);
		tmp = tmp->next;
	}
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
///for each line
	print_to_cor(info->data, fd);
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
