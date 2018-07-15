/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 21:42:07 by aorji             #+#    #+#             */
/*   Updated: 2018/07/14 21:42:09 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		status_found(t_label **l, char *tmp)
{
	t_label	*label;

	label = *l;
	while (label)
	{
		if (!ft_strcmp(label->name, tmp))
		{
			label->found = 1;
			break ;
		}
		label = label->next;
	}
}

static void		ft_line(char **line, t_name_comm *info, int i)
{
	(*line) += i + 1;
	(info->index) += i + 1;
	(*line) = ws((*line), info);
}

char			*label(char *line, t_name_comm *info, char *f_name, int *j)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((line)[i] && ft_isalnum((line)[i]))
		i++;
	if ((line)[i] != LABEL_CHAR && !(*j = 0))
		return (ft_strsub(line, 0, ft_strlen(line)));
	(info->in)++;
	if (info->count != 2 && (*j = ERROR))
	{
		syntax_error(SYNT_ERROR, f_name);
		return (ft_strsub(line, 0, ft_strlen(line)));
	}
	tmp = ft_strsub((line), 0, i);
	if (!find_label(info, tmp))
		add_label(line, info);
	add_data(tmp, 0, info);
	status_found(&(info->label), tmp);
	ft_strdel(&tmp);
	ft_line(&line, info, i);
	if (!ft_strlen(line) && (*j = 2))
		return (ft_strsub(line, 0, ft_strlen(line)));
	*j = 1;
	return (ft_strsub(line, 0, ft_strlen(line)));
}
