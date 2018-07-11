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

void	print_byte(int fd, int i, int size)
{
	if (size == 2)
		i <<= 8;
	else if (size == 4)
		i <<= 24;
	write(fd, &i, size);
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

	while (name[i])
	{
		print_byte(fd, name[i], 1);
		i++;
		size--;
	}
	while (size)
	{
		print_byte(fd, 0, 1);
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