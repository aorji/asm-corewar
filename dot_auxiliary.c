/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_auxiliary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:21:00 by aorji             #+#    #+#             */
/*   Updated: 2018/07/15 03:21:06 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		add_name_comm(t_name_comm *info, char *line)
{
	if (info->name)
	{
		info->name_comm.name = noleak_strjoin(info->name_comm.name,
			line, &(info->name_comm.name));
		info->name_comm.name = noleak_strjoin(info->name_comm.name,
			"\n", &(info->name_comm.name));
	}
	else if (info->comment)
	{
		info->name_comm.comment = noleak_strjoin(info->name_comm.comment,
			line, &(info->name_comm.comment));
		info->name_comm.comment = noleak_strjoin(info->name_comm.comment,
			"\n", &(info->name_comm.comment));
	}
	ft_strdel(&line);
}

static	void	join_name_comm(t_name_comm *info, char *tmp2)
{
	if (info->name)
		info->name_comm.name = noleak_strjoin(info->name_comm.name,
			tmp2, &(info->name_comm.name));
	else if (info->comment)
		info->name_comm.comment = noleak_strjoin(info->name_comm.comment,
			tmp2, &(info->name_comm.comment));
}

int				find_close(char *line, int close,
	t_name_comm *info, char *f_name)
{
	char	*tmp;
	int		tr;
	int		i;

	i = 0;
	tmp = ft_strsub(line, 0, close);
	join_name_comm(info, tmp);
	ft_strdel(&tmp);
	tmp = line;
	info->tab = 0;
	while (i < close + 1)
	{
		(line[i] == '\t') ? add_tab(info) : 0;
		i++;
	}
	info->index += close + 1;
	line += close + 1;
	line = ws(line, info);
	ft_strdel(&tmp);
	if ((tr = trash(line, 0)) != -1)
	{
		info->index += tr;
		return (trash_error(*info, line, tr, f_name));
	}
	return (1);
}

int				next_line_quatation(t_name_comm *info, char *f_name, char *line)
{
	int		close;
	int		i;

	i = 0;
	close = -1;
	info->index = 0;
	while (get_next_line(info->fd, &line, &i) == 1 &&
		(info->row)++ && (close = find_quatation(line, 0)) == -1)
	{
		if (!line)
			continue ;
		add_name_comm(info, line);
	}
	if (close == -1)
		return (lexical_error_q(info->name, f_name));
	else
		return (find_close(line, close, info, f_name));
	return (1);
}

int				if_find_close(t_name_comm *info, char **line,
	int close, char *name)
{
	int tr;

	if (info->name)
		info->name_comm.name = ft_strsub((*line), 0, close);
	else
		info->name_comm.comment = ft_strsub((*line), 0, close);
	info->index += close + 1;
	(*line) += close + 1;
	(*line) = ws((*line), info);
	if ((tr = trash((*line), 0)) != -1)
	{
		info->index += tr;
		return (trash_error(*info, (*line), tr, name));
	}
	return (1);
}
