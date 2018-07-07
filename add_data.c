/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 17:30:54 by aorji             #+#    #+#             */
/*   Updated: 2018/07/07 17:30:55 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int is_full(t_data *tmp, int i)
{
	if (i >= 2 && i <= 4)
		return (0);
	if (i == 0)
		return (1);
	if (i == 1 && tmp->func)
		return (1);
	if (i == 1 && !(tmp->func))
		return (0);
	return (1);
}

void	add_data(char *str, int i, t_name_comm *info)
{
	t_data *tmp;

	if (!(info->data))
	{
		info->data = (t_data *)malloc(sizeof(t_data));
		info->data->label = NULL;
		info->data->func = NULL;
		info->data->arg1 = NULL;
		info->data->arg2 = NULL;
		info->data->arg3 = NULL;
		info->data->next = NULL;
		if (i == 0)
			info->data->label = ft_strdup(str);
		else if (i == 1)
			info->data->func = ft_strdup(str);
	}
	else
	{
		tmp = info->data;
		while (tmp->next)
			tmp = tmp->next;
		if (!is_full(tmp, i))
		{
			if (i == 1)
				tmp->func = ft_strdup(str);
			if (i == 2)
				tmp->arg1 = ft_strdup(str);
			if (i == 3)
				tmp->arg2 = ft_strdup(str);
			if (i == 4)
				tmp->arg3 = ft_strdup(str);
		}
		else 
		{
			tmp->next = (t_data *)malloc(sizeof(t_data));
			tmp->next->label = NULL;
			tmp->next->func = NULL;
			tmp->next->arg1 = NULL;
			tmp->next->arg2 = NULL;
			tmp->next->arg3 = NULL;
			tmp->next->next = NULL;
			if (i == 0)
				tmp->next->label = ft_strdup(str);
			if (i == 1)
				tmp->next->func = ft_strdup(str);
		}
	}
}
