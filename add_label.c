/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 21:43:12 by aorji             #+#    #+#             */
/*   Updated: 2018/07/14 21:43:16 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	find_label(t_name_comm *info, char *name)
{
	t_label	*label;
	int f;

	f = 0;
	label = info->label;
	while (label)
	{
		if (!ft_strcmp(label->name, name))
			f++;
		label = label->next;
	}
	return (f);
}

static void create_label(t_name_comm *info, t_label **label, char *line, int i)
{
	*label = (t_label*)malloc(sizeof(t_label));
	(*label)->name = ft_strsub(line, 0, i);
	(*label)->x = info->row;
	(*label)->y = info->index + 1 + info->tab;
	(*label)->found = 0;
	(*label)->next = NULL;
}

int	add_label(char *line, t_name_comm *info)
{
	int i;
	t_label *tmp;
	char *label;

	i = 0;
	while (line[i] && ft_isalnum(line[i]) && ++i)
		(*line == '\t') ? add_tab(info) : 0;
	if (!info->label)
		create_label(info, &(info->label), line, i);
	else
	{
		tmp = info->label;
		label = ft_strsub(line, 0, i);
		if (find_label(info, label))
		{
			free(label);
			return (i);
		}
		free(label);
		while (tmp->next)
			tmp = tmp->next;
		create_label(info, &(tmp->next), line, i);
	}
	return (i);
}
