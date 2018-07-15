/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 12:23:54 by aorji             #+#    #+#             */
/*   Updated: 2018/07/09 12:23:56 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		part3(char *str, t_data **data)
{
	if (!ft_strcmp(str, "lld"))
	{
		(*data)->op = 13;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
	else if (!ft_strcmp(str, "lldi"))
	{
		(*data)->op = 14;
		(*data)->co = 1;
		(*data)->ls = 2;
	}
	else if (!ft_strcmp(str, "lfork"))
	{
		(*data)->op = 15;
		(*data)->co = 0;
		(*data)->ls = 2;
	}
	else if (!ft_strcmp(str, "aff"))
	{
		(*data)->op = 16;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
}

static void		part2(char *str, t_data **data)
{
	if (!ft_strcmp(str, "zjmp"))
	{
		(*data)->op = 9;
		(*data)->co = 0;
		(*data)->ls = 2;
	}
	else if (!ft_strcmp(str, "ldi"))
	{
		(*data)->op = 10;
		(*data)->co = 1;
		(*data)->ls = 2;
	}
	else if (!ft_strcmp(str, "sti"))
	{
		(*data)->op = 11;
		(*data)->co = 1;
		(*data)->ls = 2;
	}
	else if (!ft_strcmp(str, "fork"))
	{
		(*data)->op = 12;
		(*data)->co = 0;
		(*data)->ls = 2;
	}
}

static void		part1(char *str, t_data **data)
{
	if (!ft_strcmp(str, "sub"))
	{
		(*data)->op = 5;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
	else if (!ft_strcmp(str, "and"))
	{
		(*data)->op = 6;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
	else if (!ft_strcmp(str, "or"))
	{
		(*data)->op = 7;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
	else if (!ft_strcmp(str, "xor"))
	{
		(*data)->op = 8;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
}

static void		part0(char *str, t_data **data)
{
	if (!ft_strcmp(str, "live"))
	{
		(*data)->op = 1;
		(*data)->co = 0;
		(*data)->ls = 4;
	}
	else if (!ft_strcmp(str, "ld"))
	{
		(*data)->op = 2;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
	else if (!ft_strcmp(str, "st"))
	{
		(*data)->op = 3;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
	else if (!ft_strcmp(str, "add"))
	{
		(*data)->op = 4;
		(*data)->co = 1;
		(*data)->ls = 4;
	}
}

void			op_ls_co(char *str, t_data **data)
{
	part0(str, data);
	part1(str, data);
	part2(str, data);
	part3(str, data);
}
