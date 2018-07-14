/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 11:57:00 by aorji             #+#    #+#             */
/*   Updated: 2018/06/28 11:57:02 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	usage_error(char *str, char *f_name)
{
	write (2, str, ft_strlen(str));
	if (f_name)
	{
		write(2, "\"", 1);
		write (2, f_name, ft_strlen(f_name));
		write(2, "\"", 1);
	}
	write(2, "\n", 1);
	return (ERROR);
}

char	*sep_error(t_name_comm *info, char *f_name)
{
	write(2, SEP_ERROR, 32);
	ft_putnbr(info->row);
	write(2, ":", 1);
	ft_putnbr((info->index) + (info->tab) + 1);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (NULL);
}	

char	*instract_error(t_name_comm *info, char *f_name)
{
	write(2, INSTRUCT_ERROR, 19);
	ft_putnbr(info->row);
	write(2, ":", 1);
	ft_putnbr(info->index + 1 + info->tab);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (NULL);
}

int label_error(char *name, int x, int y, char *f_name)
{
	write(2, LABEL_ERROR, 14);
	write(2, "\"", 1);
	write(2, name, ft_strlen(name));
	write(2, "\" [", 3);
	ft_putnbr(x);
	write(2, ":", 1);
	ft_putnbr(y);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int end_error(char *f_name)
{
	write(2, END_ERROR, 84);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}
