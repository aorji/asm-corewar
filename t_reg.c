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

static void	move_one(char **line, t_name_comm *info)
{
	(*line)++;
	(info->index)++;
}

char		*t_reg_arg1(char *line, t_name_comm *info, char *f_name)
{
	int	d_len;
	int	n;

	move_one(&line, info);
	n = atoi(line);
	d_len = ft_number_size(n);
	if (n <= REG_NUMBER && n >= 0)
	{
		line += d_len;
		info->index += d_len;
		line = ws(line, info);
		if (*line == SEPARATOR_CHAR)
			move_one(&line, info);
		else
			return (sep_error(info, f_name));
	}
	else
	{
		trash_error(*info, line, 0, f_name);
		return (NULL);
	}
	return (line);
}

char		*t_reg_arg2(char *line, t_name_comm *info, char *f_name)
{
	int	d_len;
	int	n;
	int	tr;

	move_one(&line, info);
	n = atoi(line);
	d_len = ft_number_size(n);
	if (n <= REG_NUMBER && n >= 0)
	{
		line += d_len;
		info->index += d_len;
		line = ws(line, info);
		if ((tr = trash(line, 0)) != -1)
		{
			info->index += tr;
			trash_error(*info, line, 0, f_name);
			return (NULL);
		}
		return (line);
	}
	else
	{
		trash_error(*info, line, 0, f_name);
		return (NULL);
	}
}
