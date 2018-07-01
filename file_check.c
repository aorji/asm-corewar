/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:33:42 by nrepak            #+#    #+#             */
/*   Updated: 2018/06/26 19:33:44 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

static char	*white_spaces(char *line, t_name_comm *info)
{
	int		j;

	j = 0;
	while (line[info->index] == ' ' || line[info->index] == '\t')
	{
		if (*line == '\t')
			add_tab(info);
		(info->index)++;
	}
	if (!line[info->index])
		return(NULL);
	j = ft_strlen(line) - 1;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j--;
	return (ft_strsub(line, info->index, j - info->index + 1));
}

int			file_check(t_name_comm *info, char *f_name)
{
	char	*line;
	char	*tmp;

	while ((get_next_line(info->fd, &line) == 1) && ++(info->row))
	{
		info->index = 0;
		info->tab = 0;
		tmp = line;
		// printf("%s\n", line);
		line = white_spaces(line, info);
		free(tmp);
		if (!line)
			continue;
		if (dot_check(line, f_name, info) == ERROR)
			return(ERROR);
		if (st_check(line, info, f_name) == ERROR)
			return (ERROR);
		// if (live_check(line) == ERROR)
		// 	return (ERROR);
		// if (ld_check(line) == ERROR)
		// 	return (ERROR);
	}
	if (info->count != 2)
			return (syntax_error(SYNT_ERROR, f_name));
	return (1);
}
