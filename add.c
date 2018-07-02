/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:59:09 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 15:59:10 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *arg3(char *line, t_name_comm *info)
{
	if (line[0] == 'r')
		return (t_reg_arg2(line, info));
	else
		return (instract_error(info));
}

static char *arg1(char *line, t_name_comm *info)
{
	if (line[0] == 'r')
		return (t_reg_arg1(line, info));
	else
		return (instract_error(info));
}

int	add_sub(char *line, t_name_comm *info, char *f_name)
{
	if (ft_strncmp(line, "add", 3) && ft_strncmp(line, "sub", 3))
		return (0);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	line += 3;
	(info->index) += 3;
	line = ws(line, info);
	line = arg1(line, info);
	if (!line)
		return (ERROR);
	line = ws(line, info);
	line = arg1(line, info);
	if (!line)
		return (ERROR);
	line = ws(line, info);
	line = arg3(line, info);
	if (!line)
		return (ERROR);
	return (1);
}
