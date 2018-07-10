/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 21:27:21 by aorji             #+#    #+#             */
/*   Updated: 2018/07/10 21:27:23 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_ind(t_data *data, t_data *tmp, char *arg, int fd)
{
	char *tmp1;
	int n;
	int len;

	if (arg[0] == ':')
	{
		arg++;
		n = n_byte(data, arg) - tmp->n;
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
		n = n_byte(data, arg) - tmp->n;
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

void choose_type(t_data *data, t_data *tmp, char *arg, int fd)
{
	if (arg && arg[0] == 'r')
		ft_reg(++arg, fd);
	else if (arg && arg[0] == '%')
		ft_dir(data, tmp, ++arg, fd);
	else if (arg)
		ft_ind(data, tmp, arg, fd);
}
