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
	int n;

	if (arg[0] == ':')
		n = n_byte(data, ++arg) - tmp->n;
	else
		n = ft_atoi(arg);
	print_byte(fd, n, 2);
}

static void	ft_dir(t_data *data, t_data *tmp, char *arg, int fd)
{
	int n;

	if (arg[0] == ':')
		n = n_byte(data, ++arg) - tmp->n;
	else
		n = ft_atoi(arg);
	print_byte(fd, n, tmp->ls);
}

void choose_type(t_data *data, t_data *tmp, char *arg, int fd)
{
	if (arg && arg[0] == 'r')
		print_byte(fd, ft_atoi(++arg), 1);
	else if (arg && arg[0] == '%')
		ft_dir(data, tmp, ++arg, fd);
	else if (arg)
		ft_ind(data, tmp, arg, fd);
}
