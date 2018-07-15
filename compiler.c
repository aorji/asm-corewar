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

static void		print_codage(t_data *data, int fd)
{
	int first;
	int second;
	int third;
	int res;

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
		print_byte(fd, res, 1);
	}
}

static void		print_to_cor(t_data *data, int fd)
{
	t_data *tmp;

	tmp = data;
	while (tmp)
	{
		if (tmp->op)
			print_byte(fd, tmp->op, 1);
		print_codage(tmp, fd);
		choose_type(data, tmp, tmp->arg1, fd);
		choose_type(data, tmp, tmp->arg2, fd);
		choose_type(data, tmp, tmp->arg3, fd);
		tmp = tmp->next;
	}
}

static void		push_data(int fd, t_name_comm *info, int size)
{
	int i;

	i = 0xf383ea;
	i <<= 8;
	write(fd, &i, 4);
	bot_name_comm(fd, info->name_comm.name, 128);
	print_byte(fd, 0, 4);
	print_byte(fd, size, 4);
	bot_name_comm(fd, info->name_comm.comment, 2048);
	print_byte(fd, 0, 4);
	print_to_cor(info->data, fd);
}

int				binary_code(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == 'r')
		return (T_REG);
	if (arg[0] == '%')
		return (T_DIR);
	return (T_IND);
}

void			compiler(t_name_comm *info, char *name)
{
	int		size;
	int		fd;
	char	*tmp;

	size = bot_size(info);
	tmp = ft_strjoin(name, ".cor");
	fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	ft_strdel(&tmp);
	push_data(fd, info, size);
}
