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
	j = ft_strlen(line);
	return (ft_strsub(line, info->index, j - info->index + 1));
}

int			file_check(t_name_comm *info, char *f_name)
{
	char	*line;
	char	*tmp;
	int		i;
	int		end;

	end = 1;
	line = NULL;
	while ((get_next_line(info->fd, &line, &end) == 1) && ++(info->row))
	{
		info->index = 0;
		info->tab = 0;
		tmp = line;
		line = white_spaces(line, info);
		free(tmp);
		if (!line)
			continue;
		if (line[0] == COMMENT_CHAR)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = dot(line, f_name, info)) == ERROR)
		{
			ft_strdel(&line);
			return(ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		tmp = line;
		line = label(line, info, f_name, &i);
		free(tmp);
		if (i == 2)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = sti(line, info, f_name)) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = st(line, info, f_name)) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = xor_and_or(line, info, f_name)) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = ldi_lldi(line, info, f_name)) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = ld_lld(line, info, f_name)) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = live_zjmp_fork_lfork(line, info, f_name)) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = add_sub(line, info, f_name)) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		if ((i = aff(line, info, f_name)) == ERROR)
		{
			free(line);
			line = NULL;
			return (ERROR);
		}
		if (i)
		{
			ft_strdel(&line);
			continue;
		}
		else
		{
			unknown_error(*info, line, f_name);
			free(line);
			return (ERROR);
		}
	}
	if (!end)
		return (end_error(f_name));
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	if (!(info->in))
		return (trash_error(*info, "(null)", 0, f_name));
	return (1);
}
