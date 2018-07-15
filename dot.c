/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:32:21 by nrepak            #+#    #+#             */
/*   Updated: 2018/07/15 15:32:26 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			find_quatation(char *line, int i)
{
	if (!line)
		return (-1);
	while (line[i] != '\"' && line[i])
		i++;
	if (line[i] == '\"')
		return (i);
	return (-1);
}

static int	close_quatation(char *line, t_name_comm *info, char *f_name)
{
	int close;

	if ((close = find_quatation(line, 0)) != -1)
		return (if_find_close(info, &line, close, f_name));
	else
	{
		if (info->name)
		{
			info->name_comm.name = ft_strsub(line, 0, ft_strlen(line));
			info->name_comm.name = noleak_strjoin(info->name_comm.name,
				"\n", &(info->name_comm.name));
		}
		else
		{
			info->name_comm.comment = ft_strsub(line, 0, ft_strlen(line));
			info->name_comm.comment = noleak_strjoin(info->name_comm.comment,
				"\n", &(info->name_comm.comment));
		}
		return (next_line_quatation(info, f_name, line));
	}
}

static void	name(t_name_comm *info, char **line)
{
	info->count++;
	info->name = 1;
	info->comment = 0;
	(*line) += 4;
	(info->index) += 4;
}

static void	comm(t_name_comm *info, char **line)
{
	info->name = 0;
	info->comment = 1;
	info->count++;
	(*line) += 7;
	(info->index) += 7;
}

int			dot(char *line, char *f_name, t_name_comm *info)
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
