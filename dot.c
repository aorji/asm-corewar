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
	while (line[i] != '\"' && line[i])
		i++;
	if (line[i] == '\"')
		return (i);
	return (-1);
}

static	int	next_line_quatation(t_name_comm *info, char *f_name)
{
	char	*line;
	int		close;	
	int		tr;
	int i = 0;
	int k = 0;
	close = -1;
	info->index = 0;
	while (get_next_line(info->fd, &line, &k) == 1 && (info->row)++ && (close = find_quatation(line, 0)) == -1)
			continue; 
	if (close == -1)
		return (lexical_error_q(info->name, f_name));
	else
	{
		info->tab = 0;
		while (i < close + 1)
		{
			if (line[i] == '\t')
				add_tab(info);
			i++;
		}
		info->index += close + 1;
		line += close + 1;
		line = ws(line, info);
		if ((tr = trash(line, close + 1)) != -1)
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
		return (next_line_quatation(info, f_name)); //-1 - no quat, 1 - find
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
		{
			info->count++;
			info->name = 1;
			info->comment = 0;
			line += 4;
			(info->index) += 4;
		}
		else
		{
			info->name = 0;
			info->comment = 1;
			info->count++;
			line += 7;
			(info->index) += 7;
		}
		if (info->count > 2)
			return (syntax_error(SYNT_ERROR, f_name));
		while (*line == ' ' || *line == '\t')
		{
			if (*line == '\t')
				add_tab(info);
			line++;
			(info->index)++;
		}
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
