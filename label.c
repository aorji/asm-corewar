/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:22:43 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 13:22:44 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*label_arg2(char *line, t_name_comm *info, char *f_name)
{
	int	n;
	int	tr;

	info->index++;
	line++;
	n = add_label(line, info);
	info->index += n;
	line += n;
	line = ws(line, info);
	if ((tr = trash(line, 0)) != -1)
	{
		info->index += tr;
		trash_error(*info, line, 0, f_name);
		return (NULL);
	}
	return (line);
}

char	*label_arg1(char *line, t_name_comm *info, char *f_name)
{
	int	n;

	info->index++;
	line++;
	n = add_label(line, info);
	info->index += n;
	line += n;
	line = ws(line, info);
	if (*line == SEPARATOR_CHAR)
	{
		line++;
		(info->index)++;
	}
	else
		return (sep_error(info, f_name));
	return (line);
}
