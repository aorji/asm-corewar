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

static int open_quotation(char *line, int *i, int *j, int *column) 
{
	while ((line[*i] != ' ' && line[*i] != '\t') && line[*i])
		(*i)++;
	while ((line[*i] == ' ' || line[*i] == '\t') && line[*i])
		(*i)++;
	*j = *i;
	(*column) = *i + 2;
	if (line[(*i)++] != '\"')
		return (0);
	return (1);
}

static int name_exist(int *column, char *line, t_name_comm *info)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!open_quotation(line, &i, &j, column))
		return (0);
	while (line[i] != '\"' && line[i])
		i++;
	(*column) = i + 2;
	if (!(line[i]))
		return (0);
	if (line[0] == 'n')
		info->name = ft_strsub(line, j + 1, i - j - 1);
	else
		info->comment = ft_strsub(line, j + 1, i - j - 1);
	return (1);
}

int	name_comm_error(char *line, int *column, t_name_comm *info)
{
	if (line[0] == '.')
	{
		line++;
		(*column)++;
		if (!ft_strncmp(line, "name", 4) || !ft_strncmp(line, "comment", 7))
			if (name_exist(column, line, info))
			{
				++(info->count);
				return (1);
			}
		return (0);
	}
	return (1);
}
