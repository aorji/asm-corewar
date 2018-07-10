/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxliary.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 20:08:59 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 20:09:00 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int trash(char *line, int i)
{
	int extra;

	extra = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR || line[i] == ';')
			return (-1);
		if (line[i] != ' ' && line[i] != '\t')
			return (extra);
		i++;
		extra++;
	}
	return (-1);
}

void	add_tab(t_name_comm *info)
{
	int a;
	int b;
	int c;

	a = info->index + info->tab;
	b = a / 4;
	c = b * 4;
	info->tab += 3 - (a - c);
}

char*	ws(char *line, t_name_comm *info)
{
	while (*line && (*line == ' ' || *line == '\t'))
	{
		if (*line == '\t')
			add_tab(info);
		(info->index)++;
		line++;
	}
	return (line);
}
