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

char	*t_dir_arg1(char *line, t_name_comm *info, char *f_name)
{
	int	n;

	line++;
	(info->index)++;
	line = ws(line, info);
	if (line[0] == LABEL_CHAR)
		return (label_arg1(line, info, f_name));
	else
	{
		if (((n = atoi(line)) != 0) || (line[0] == 48 && (line[1] == ' '
			|| line[1] == '\t' || line[1] == SEPARATOR_CHAR)))
			return (t_int_arg1(line, info, f_name));
		else
			return (instract_error(info, f_name));
	}
}

char	*t_dir_arg2(char *line, t_name_comm *info, char *f_name)
{
	int	n;

	line++;
	(info->index)++;
	line = ws(line, info);
	if (line[0] == LABEL_CHAR)
		return (label_arg2(line, info, f_name));
	else
	{
		if ((n = atoi(line)) != 0 || (line[0] == 48 && (line[1] == ' '
			|| line[1] == '\t' || line[1] == '\0')))
			return (t_int_arg2(line, info, f_name));
		else
			return (instract_error(info, f_name));
	}
}
