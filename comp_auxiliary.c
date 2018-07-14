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

static char *trim(char *str)
{
	int i;

	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	return(ft_strsub(str, 0, i + 1));
}

void	print_byte(int fd, int i, int size)
{
	char	c[4];
	char	move[4];
	int		k = 0;

	while (k < size)
	{
		c[k] = i;
		if (c[k] < 0)
		{
			move[k] = 1;
			c[k] -= 128;
		}
		else
			move[k] = 0;
		i >>= 8;
		k++;
	}
	k = 0;
	i = 0;
	while (k < size)
	{
		if (move[k])
			i |= c[k] + 128;
		else
			i |= c[k];
		if (k + 1 < size)
			i <<= 8;
		k++;
	}
	write(fd, &i, size);
}

int n_byte(t_data *data, char *name)
{
	char *str1;
	char *str2;

	while (data)
	{
		str1 = trim(data->label);
		str2 = trim(name);
		if (data->label && !ft_strcmp(str1, str2))
		{
			ft_strdel(&str1);
			ft_strdel(&str2);
			return (data->n);
		}
		data = data->next;
		ft_strdel(&str1);
		ft_strdel(&str2);
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