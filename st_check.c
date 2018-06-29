/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:24:30 by aorji             #+#    #+#             */
/*   Updated: 2018/06/29 18:24:36 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *arg1(char *line, t_name_comm *info)
{
	int n;
	int	d_len;

	if (line[0] == 'r')
	{
		line++;
		(info->index)++;
		d_len = ft_number_size((n = atoi(line)));
		if (n <= REG_NUMBER && n >= 1)
		{
			line += d_len;
			info->index += d_len;
			line = ws(line, info);
			if (*line == ',')
			{
				line++;
				(info->index)++;
			}
			else
				return (sep_error(info));
		}
		else
			return (st_error());
	}
	else
		return (st_error());
	return (ws(line, info));
}

int	st_check(char *line, t_name_comm *info, char *f_name)
{
	if (ft_strncmp(line, "st", 2))
		return (1);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	line += 2;
	(info->index) += 2;
	line = ws(line, info);
	line = arg1(line, info);
	// ОБРАБОТАТЬ ВТОРОЙ ПАРАМЕТР
	if (!line)
		return (ERROR);
	return (1);
}
