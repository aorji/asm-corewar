/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_reg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:06:15 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 13:06:16 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char *t_reg_arg1(char *line, t_name_comm *info)
{
	int d_len;
	int n;
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
	{
		trash_error(*info, line, 0);
		return (NULL);
	}
	return (line);
}

char *t_reg_arg2(char *line, t_name_comm *info)
{
	int d_len;
	int n;
	int tr;

	line++;
	(info->index)++;
	d_len = ft_number_size((n = atoi(line)));
	if (n <= REG_NUMBER && n >= 1)
	{
		line += d_len;
		info->index += d_len;
		line = ws(line, info);
		if ((tr = trash(line, 0)) != -1)
		{
			info->index += tr;
			trash_error(*info, line, 0);
			return (NULL);
		}
		return (line);
	}
	else
	{
		trash_error(*info, line, 0);
		return (NULL);
	}
}
