/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 21:44:12 by aorji             #+#    #+#             */
/*   Updated: 2018/07/10 21:44:14 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_struct(t_data *data)
{
	t_data *tmp;

	tmp = data;
	while (tmp)
	{
		ft_putstr("--------------------\n");
		ft_putstr("label = ");
		ft_putstr(tmp->label);
		write(1, "\n", 1);
		ft_putstr("func = ");
		ft_putstr(tmp->func);
		write(1, "\n", 1);
		ft_putstr("op = ");
		ft_putnbr_fd(tmp->op, 1);
		write(1, "\n", 1);
		ft_putstr("co = ");
		ft_putnbr_fd(tmp->co, 1);
		write(1, "\n", 1);
		ft_putstr("ls = ");
		ft_putnbr_fd(tmp->ls, 1);
		write(1, "\n", 1);
		ft_putstr("n = ");
		ft_putnbr_fd(tmp->n, 1);
		write(1, "\n", 1);
		ft_putstr("arg1 = ");
		ft_putstr(tmp->arg1);
		write(1, "\n", 1);
		ft_putstr("arg2 = ");
		ft_putstr(tmp->arg2);
		write(1, "\n", 1);
		ft_putstr("arg3 = ");
		ft_putstr(tmp->arg3);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	write(1, "\n", 1);
}