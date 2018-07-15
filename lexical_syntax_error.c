/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_syntax_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 22:03:25 by aorji             #+#    #+#             */
/*   Updated: 2018/07/14 22:03:28 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	lexical_error(t_name_comm info, char *f_name)
{
	write(2, LEX_ERROR, 18);
	ft_putnbr(info.row);
	write(2, ":", 1);
	ft_putnbr(info.index + 1 + info.tab);
	write(2, "] ", 2);
	write(2, "in the ", 7);
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int	lexical_error_q(int i, char *f_name)
{
	write(2, NO_QUAT_ERROR, 28);
	if (i)
		write(2, "for \"name\" in the \"", 20);
	else
		write(2, "for \"comment\" in the \"", 22);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}

int	syntax_error(char *str, char *f_name)
{
	write(2, str, ft_strlen(str));
	write(2, NAME_COMM, ft_strlen(NAME_COMM));
	write(2, "\"", 1);
	write(2, f_name, ft_strlen(f_name));
	write(2, "\"", 1);
	write(2, "\n", 1);
	return (ERROR);
}
