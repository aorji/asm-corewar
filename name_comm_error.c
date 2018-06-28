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

static int open_quotation(char *line, int *i, int *j, int *column) 
{
	while ((line[*i] != ' ' && line[*i] != '\t') && line[*i])
		(*i)++;
	while ((line[*i] == ' ' || line[*i] == '\t') && line[*i])
		(*i)++;
	*j = *i;
	(*column) = *i + 2;
	if (line[(*i)++] != '\"')
		return (-1);
	return (*i);
}

static int trash(char *line, int q)
{
	int i;

	i = 0;
	while (line[q] && ++i)
	{
		if (line[q] != ' ' && line[q] != '\t')
			return (i);
		q++;
	}
	return (0);
}

static int name_exist(int *column, char *line, t_name_comm *info, int *row)
{
	int i;
	int j;
	int o;
	int q;
	int g;

	j = 0;
	i = 0;
	g = 0;
	if ((o = open_quotation(line, &i, &j, column)) == -1)
		return (0);
	while (line[i] != '\"' && line[i])
		i++;
	(*column) = i + 2;
	printf("%d\n", *column);
	if (line[0] == 'n')
	{
		if (close_quatation(line, o) == -1) //no quatation, try to find in next lines
		{
			while (((g = get_next_line(info->fd, &line)) == 1) && (*row)++ && ((q = close_quatation(line, 0)) == -1))
				continue;
			i = q;
			*column = q + 2;
			if (!g) 
				return (0);
			while (line[q+1] && (line[q+1] == ' ' || line[q+1] == '\t'))
			{
				q++;
				(*column)++;
			}
		}
		else
		{
			while (line[i+1] && (line[i+1] == ' ' || line[i+1] == '\t'))
			{
					i++;
					(*column)++;
			}
			(*column) += 1;
		}
		if (trash(line, i + 1))
			return (0);
		info->name = 1;
	}
	if (line[0] == 'c')
	{
		if (close_quatation(line, o) == -1) //no quatation, try to find in next lines
		{
			while (((g = get_next_line(info->fd, &line)) == 1) && (*row)++ && ((q = close_quatation(line, 0)) == -1))
				continue;
			i = q;
			*column = q + 2;
			if (!g) 
				return (0);
			while (line[q+1] && (line[q+1] == ' ' || line[q+1] == '\t'))
			{
				q++;
				(*column)++;
			}
		}
		else
		{
			while (line[i+1] && (line[i+1] == ' ' || line[i+1] == '\t'))
			{
					i++;
					(*column)++;
			}
			(*column) += 1;
		}
		if (trash(line, i + 1))
			return (0);
		info->comment = 1;
	}
	return (1);
}

int	name_comm_error(char *line, int *column, t_name_comm *info, int *row)
{
	if (line[0] == '.')
	{
		line++;
		(*column)++;
		if (!ft_strncmp(line, "name", 4) || !ft_strncmp(line, "comment", 7))
			if (name_exist(column, line, info, row))
			{
				++(info->count);
				return (1);
			}
		return (0);
	}
	return (1);
}
