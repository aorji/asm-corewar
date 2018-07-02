/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:22:43 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 13:22:44 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	add_label(char *line, t_name_comm *info)
{
	int i = 0;
	t_label *tmp;

	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != ',')
	{
		if (*line == '\t')
			add_tab(info);
		i++;
	}
	if (!info->label)
	{
		info->label = (t_label*)malloc(sizeof(t_label));
		info->label->name = ft_strsub(line, 0, i);
		info->label->found = 0;
		info->label->next = NULL;
	}
	else
	{
		tmp = info->label;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_label*)malloc(sizeof(t_label));
		tmp->next->name = ft_strsub(line, 0, i);
		tmp->next->found = 0;
		tmp->next->next = NULL;
	}
	return (i);
}

char *label_arg2(char *line, t_name_comm *info)
{
	int n;
	int tr;
	
	info->index++;
	line++;
	n = add_label(line, info);
	info->index += n;
	line += n;
	line = ws(line, info);
	if ((tr = trash(line, 0)) != -1)
	{
		info->index += tr;
		trash_error(*info, line, 0);
		return (NULL);
	}
	return (line);
}

char *label_arg1(char *line, t_name_comm *info)
{
	int n;
	
	info->index++;
	line++;
	n = add_label(line, info);
	info->index += n;
	line += n;
	line = ws(line, info);
	if (*line == ',')
	{
		line++;
		(info->index)++;
	}
	else
	{
		return (sep_error(info));
	}
	return (line);
}
