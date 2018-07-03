/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 16:28:34 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 16:28:35 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *arg3(char *line, t_name_comm *info)
{
	if (line[0] == 'r')
		return (t_reg_arg2(line, info));
	else if (line[0] == '%')
		return (t_dir_arg2(line, info));
	else
		return (instract_error(info));
}

static char *arg2(char *line, t_name_comm *info)
{
	int n;

	if (line[0] == 'r')
		return (t_reg_arg1(line, info));
	else if ((n = atoi(line)) != 0 || (line[0] == '0' 
		&& (line[1] == ' ' || line[1] == '\t' || line[1] == ',')))
		return (t_int_arg1(line, info));
	else if (line[0] == '%')
		return (t_dir_arg1(line, info));
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

int	sti(char *line, t_name_comm *info, char *f_name)
{
	if (ft_strncmp(line, "sti", 3))
		return (0);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	(info->in)++;
	line += 3;
	(info->index) += 3;
	line = ws(line, info);
	line = arg1(line, info);
	if (!line)
		return (ERROR);
	line = ws(line, info);
	line = arg2(line, info);
	if (!line)
		return (ERROR);
	line = ws(line, info);
	line = arg3(line, info);
	if (!line)
		return (ERROR);
	return (1);
}