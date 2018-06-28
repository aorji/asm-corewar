/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comm_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:01:18 by aorji             #+#    #+#             */
/*   Updated: 2018/06/28 12:01:20 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int close_quatation(char *line, int i)
{
	while (line[i] != '\"' && line[i])
		i++;
	if (line[i] == '\"')
		return (i);
	return (-1);
}

static int open_quotation(char *line, int *i, int *column) 
{
	while ((line[*i] != ' ' && line[*i] != '\t') && line[*i])
		(*i)++;
	while ((line[*i] == ' ' || line[*i] == '\t') && line[*i])
		(*i)++;
	(*column) = *i + 2;
	if (line[(*i)++] != '\"')
		return (-1);
	return (*i);
}

static int trash(char *line, int q)
{
	int i;

	i = 1;
	while (line[q])
	{
		if (line[q] != ' ' && line[q] != '\t')
			return (i);
		q++;
		i++;
	}
	return (0);
}

static int find_quatation(t_name_comm *info, char **line)
{
	char *tmp;
	int close;
	int g;

	g = 0;
	while (((g = get_next_line(info->fd, line)) == 1) && (info->row)++ && ((close = close_quatation(*line, 0)) == -1))
		tmp = *line;
	info->i = close;
	info->column = close + 1;
	if (!g)
	{
		info->column = ft_strlen(tmp) + 1;
		return (0);
	}
	return (1);
}

static int check_value(char determ, char *line, int open, t_name_comm *info)
{
	int k = 0;

	if (close_quatation(line, open) == -1) //no quatation, try to find in next lines
	{
		if (!find_quatation(info, &line))
			return (0);
	}
	else
	{
		while (line[info->i + 1] && (line[info->i + 1] == ' ' || line[info->i + 1] == '\t'))
		{
				info->i++;
				(info->column)++;
		}
		if (line[info->i] && (line[info->i] == ' ' || line[info->i] == '\t'))
		{
				info->i++;
				(info->column)++;
		}
	}
	if ((k = trash(line, info->i + 1)))
	{
		info->column += k;;
		return (0);
	}
	(determ == 'n') ? info->name++ : info->comment++;
	return (1);
}

static int name_exist(char *line, t_name_comm *info)
{
	int open;

	if ((open = open_quotation(line, &(info->i), &(info->column))) == -1)
		return (0);
	while (line[info->i] != '\"' && line[info->i])
		(info->i)++;
	info->column = info->i + 1;
	if (line[0] == 'n')
		return (check_value('n', line, open, info));
	return (check_value('c', line, open, info));
}

int	name_comm_error(char *line, t_name_comm *info)
{
	if (line[0] == '.')
	{
		line++;
		(info->column)++;
		if (!ft_strncmp(line, "name", 4) || !ft_strncmp(line, "comment", 7))
			if (name_exist(line, info))
			{
				++(info->count);
				return (1);
			}
		return (0);
	}
	return (1);
}
