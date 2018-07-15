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
		return (NULL);
	j = ft_strlen(line);
	return (ft_strsub(line, info->index, j - info->index + 1));
}

static int	part2(char **line, t_name_comm *info, char *f_name, int i)
{
	if ((i = xor_and_or((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	if ((i = ldi_lldi((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	if ((i = ld_lld((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	if ((i = live_zjmp_fork_lfork((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	if ((i = add_sub((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	if ((i = aff((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	return (unknown_error(*info, (*line), f_name));
}

static int	check_functions(char **line, t_name_comm *info, char *f_name, int i)
{
	char	*tmp;

	if (!(*line))
		return (1);
	if (**line == COMMENT_CHAR[0] || **line == COMMENT_CHAR[1])
		return (0);
	if ((i = dot((*line), f_name, info)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	tmp = (*line);
	*line = label((*line), info, f_name, &i);
	ft_strdel(&tmp);
	if (i == 2)
		return (0);
	if ((i = sti((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	if ((i = st((*line), info, f_name)) == ERROR)
		return (ERROR);
	if (i)
		return (0);
	return (part2(line, info, f_name, 0));
}

static void	ft_null(t_name_comm *info, char **tmp, char **line)
{
	info->index = 0;
	info->tab = 0;
	*tmp = *line;
}

int			file_check(t_name_comm *info, char *f_name)
{
	char	*line;
	char	*tmp;
	int		end;

	end = 1;
	line = NULL;
	while ((get_next_line(info->fd, &line, &end) == 1) && ++(info->row))
	{
		ft_null(info, &tmp, &line);
		line = white_spaces(line, info);
		ft_strdel(&tmp);
		if (check_functions(&line, info, f_name, 0) == ERROR)
		{
			ft_strdel(&line);
			return (ERROR);
		}
		ft_strdel(&line);
	}
	if (!end)
		return (end_error(f_name));
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	if (!(info->in))
		return (trash_error(*info, "(null)", 0, f_name));
	return (1);
}
