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

static int find_label(t_data *data, char *name)
{
	while (data)
	{
		if (data->label && !ft_strcmp(data->label, name))
			return (data->n);
		data = data->next;
	}
	return (-1);
}

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

static int binary_code(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == 'r')
		return (T_REG);
	if (arg[0] == '%')
		return (T_DIR);
	return (T_IND);
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

static void	ft_ind(t_data *data, t_data *tmp, char *arg, int fd)
{
	char *tmp1;
	int n;
	int len;

	if (arg[0] == ':')
	{
		arg++;
		n = find_label(data, arg) - tmp->n;
		arg = ft_itoa_base(n, 16);
	}
	else
		arg = ft_itoa_base(ft_atoi(arg), 16);
	tmp1 = arg;
	while ((int)ft_strlen(arg) > 4)
		arg++;
	ft_strdel(&tmp1);
	len = 4 - ft_strlen(arg);
	while (len)
	{
		ft_put_fd("0", fd);
		len--;
	}
	ft_put_fd(arg, fd);
}

static void	ft_dir(t_data *data, t_data *tmp, char *arg, int fd)
{
	char *tmp1;
	int n;
	int len;

	if (arg[0] == ':')
	{
		arg++;
		n = find_label(data, arg) - tmp->n;
		arg = ft_itoa_base(n, 16);
	}
	else
		arg = ft_itoa_base(ft_atoi(arg), 16);
	tmp1 = arg;
	while ((int)ft_strlen(arg) > ((tmp->ls) * 2))
		arg++;
	ft_strdel(&tmp1);
	len = ((tmp->ls) * 2) - ft_strlen(arg);
	while (len)
	{
		ft_put_fd("0", fd);
		len--;
	}
	ft_put_fd(arg, fd);
}

static void ft_reg(char *arg, int fd)
{
	char *str;

	str = ft_itoa_base(ft_atoi(arg), 16);
	if (ft_strlen(str) == 1)
		ft_put_fd("0", fd);
	ft_put_fd(str, fd);
	ft_strdel(&str);
}

static void choose_type(t_data *data, t_data *tmp, char *arg, int fd)
{
	if (arg && arg[0] == 'r')
		ft_reg(++arg, fd);
	else if (arg && arg[0] == '%')
		ft_dir(data, tmp, ++arg, fd);
	else if (arg)
		ft_ind(data, tmp, arg, fd);
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
