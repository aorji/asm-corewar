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

static int	find_label(t_name_comm *info, char *name)
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

int	add_label(char *line, t_name_comm *info)
{
	int i;
	i = 0;
	t_label *tmp;
	char *label;

	while (line[i] && ft_isalnum(line[i]))
	{
		if (*line == '\t')
			add_tab(info);
		i++;
	}
	if (!info->label)
	{
		info->label = (t_label*)malloc(sizeof(t_label));
		info->label->name = ft_strsub(line, 0, i);
		info->label->x = info->row;
		info->label->y = info->index + 1 + info->tab;
		info->label->found = 0;
		info->label->next = NULL;
	}
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
		tmp->next = (t_label*)malloc(sizeof(t_label));
		tmp->next->name = ft_strsub(line, 0, i);
		tmp->next->found = 0;
		tmp->next->x = info->row;
		tmp->next->y = info->index + 1 + info->tab;
		tmp->next->next = NULL;
	}
	return (i);
}

char *label_arg2(char *line, t_name_comm *info, char *f_name)
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
		trash_error(*info, line, 0, f_name);
		return (NULL);
	}
	return (line);
}

char *label_arg1(char *line, t_name_comm *info, char *f_name)
{
	int n;
	
	info->index++;
	line++;
	n = add_label(line, info);
	info->index += n;
	line += n;
	line = ws(line, info);
	if (*line == SEPARATOR_CHAR)
	{
		line++;
		(info->index)++;
	}
	else
		return (sep_error(info, f_name));
	return (line);
}


char	*label(char *line, t_name_comm *info, char *f_name, int *j)
{
	int		i;
	char	*tmp;
	t_label	*label;

	i = 0;
	while ((line)[i] && ft_isalnum((line)[i]))
		i++;
	if ((line)[i] != LABEL_CHAR)
	{
		*j = 0;
		return (ft_strsub(line, 0, ft_strlen(line)));
	}
	(info->in)++;
	if (info->count != 2)
	{
		syntax_error(SYNT_ERROR, f_name);
		*j = ERROR;
		return (ft_strsub(line, 0, ft_strlen(line)));
	}
	tmp = ft_strsub((line), 0, i);
	if (!find_label(info, tmp))
		add_label(line, info);
	add_data(tmp, 0, info);
	label = info->label;
	while (label)
	{
		if (!ft_strcmp(label->name, tmp))
		{
			label->found = 1;
			break;
		}
		label = label->next;
	}
	free(tmp);
	tmp = NULL;
	(line) += i + 1;
	(info->index) += i + 1;
	(line) = ws((line), info);
	if (!ft_strlen(line))
	{
		*j = 2;
		return (ft_strsub(line, 0, ft_strlen(line)));
	}
	*j = 1;
	return (ft_strsub(line, 0, ft_strlen(line)));
}
