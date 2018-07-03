/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_int.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:18:44 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 13:18:45 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char *t_int_arg2(char *line, t_name_comm *info)
{
	int tr;
	int n;

	n = 0;
	if (*line == '-')
	{
		line++;
		n++;
	}
	while (ft_isdigit(*line))
	{
		line++;
		n++;
	}
	info->index += n;
	line = ws(line, info);
	if ((tr = trash(line, 0)) != -1)
	{
		info->index += tr;
		trash_error(*info, line, 0);
		return (NULL);
	}
	return (line);
}

char *t_int_arg1(char *line, t_name_comm *info)
{
	int n;

	n = 0;
	if (*line == '-')
	{
		line++;
		n++;
	}
	while (ft_isdigit(*line))
	{
		line++;
		n++;
	}
	info->index += n;
	line = ws(line, info);
	if (*line == ',')
	{
		line++;
		(info->index)++;
	}
	else
		return (sep_error(info));
	return (line);
}
