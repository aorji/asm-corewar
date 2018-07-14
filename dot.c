/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 11:06:28 by aorji             #+#    #+#             */
/*   Updated: 2018/06/29 11:06:29 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int find_quatation(char *line, int i)
{
	if (!line)
		return (-1);
	while (line[i] != '\"' && line[i])
		i++;
	if (line[i] == '\"')
		return (i);
	return (-1);
}

static void add_name_comm(t_name_comm *info, char *line)
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

static	void join_name_comm(t_name_comm *info, char *tmp2)
{
	if (info->name)
		info->name_comm.name = noleak_strjoin(info->name_comm.name, tmp2, &(info->name_comm.name));
	else if (info->comment)
		info->name_comm.comment = noleak_strjoin(info->name_comm.comment, tmp2, &(info->name_comm.comment));
}

static	int	next_line_quatation(t_name_comm *info, char *f_name, char *line)
{
	int		close;
	char	*tmp;
	char	*tmp2;
	int		tr;
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
	{
		tmp = line;
		tmp2 = ft_strsub(line, 0, close);
		join_name_comm(info, tmp2);
		ft_strdel(&tmp2);
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
	return (1);
}

static int	close_quatation(char *line, t_name_comm *info, char *f_name)
{
	int close;
	int tr;

	if ((close = find_quatation(line, 0)) != -1)
	{
		if (info->name)
			info->name_comm.name = ft_strsub(line, 0, close);
		else
			info->name_comm.comment = ft_strsub(line, 0, close);
		info->index += close + 1;
		line += close + 1;
		line = ws(line, info);
		if ((tr = trash(line, 0)) != -1)
		{
			info->index += tr;
			return (trash_error(*info, line, tr, f_name));
		}
		return (1);
	}
	else
	{
		if (info->name)
		{
			info->name_comm.name = ft_strsub(line, 0, ft_strlen(line));
			info->name_comm.name = noleak_strjoin(info->name_comm.name, "\n", &(info->name_comm.name));
		}
		else
		{
			info->name_comm.comment = ft_strsub(line, 0, ft_strlen(line));
			info->name_comm.comment = noleak_strjoin(info->name_comm.comment, "\n", &(info->name_comm.comment));
		}
		return (next_line_quatation(info, f_name, line)); //-1 - no quat, 1 - find
	}
}

static void name(t_name_comm *info, char **line)
{
	info->count++;
	info->name = 1;
	info->comment = 0;
	(*line) += 4;
	(info->index) += 4;
}

static void comm(t_name_comm *info, char **line)
{
	info->name = 0;
	info->comment = 1;
	info->count++;
	(*line) += 7;
	(info->index) += 7;
}

int 		dot(char *line, char *f_name, t_name_comm *info)
{
	if (line[0] != '.')
		return (0);
	info->index++;
	line++;
	if (!ft_strncmp(line, "name", 4) || !ft_strncmp(line, "comment", 7))
	{
		if (!ft_strncmp(line, "name", 4))
			name(info, &line);
		else
			comm(info, &line);
		if (info->count > 2)
			return (syntax_error(SYNT_ERROR, f_name));
		line = ws(line, info);
		if (*line == '\"')
		{
			line++;
			(info->index)++;
		}
		else
			return (lexical_error(*info, f_name));
		return (close_quatation(line, info, f_name));
	}
	else
		return (lexical_error(*info, f_name));
	return (1);
}
