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

int lexical_error(int row, int column, char *f_name)
{
	write(2, LEX_ERROR, 18);
	ft_putnbr(row);
	write(2, ":", 1);
	ft_putnbr(column);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (-1);
}

int syntax_error(char *str, char *err, char *f_name)
{
	write(2, str, ft_strlen(str));
	write(2, err, ft_strlen(err));
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (-1);
}

int	usage_error(char *str, char *name)
{
	write (2, str, ft_strlen(str));
	if (name)
	{
		write(2, "\"", 1);
		write (2, name, ft_strlen(name));
		write(2, "\"", 1);
	}
	write(2, "\n", 1);
	return (USAGE_ERROR);
}