/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:04:59 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 15:05:00 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char *t_dir_arg1(char *line, t_name_comm *info)
{
	int n;

	line++;
	(info->index)++;
	line = ws(line, info);
	if (line[0] == ':')
		return (label_arg1(line, info));
	else
	{
		if (((n = atoi(line)) != 0) || (line[0] == '0' && (line[1] == ' ' || line[1] == '\t' || line[1] == ',')))
			return (t_int_arg1(line, info, n));
		else
			return (instract_error(info));
	}
}

char *t_dir_arg2(char *line, t_name_comm *info)
{
	int n;

	line++;
	(info->index)++;
	line = ws(line, info);
	if (line[0] == ':')
		return (label_arg2(line, info));
	else
	{
		if ((n = atoi(line)) != 0 || (line[0] == 0 && (line[1] == ' ' || line[1] == '\t')))
			return (t_int_arg2(line, info, n));
		else
			return (instract_error(info));
	}
}
