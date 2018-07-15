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

static int		is_full(t_data *tmp, int i)
{
	if (i >= 2 && i <= 4)
		return (0);
	if (i == 1 && !(tmp->func))
		return (0);
	return (1);
}

static	void	create_data(t_data **data)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->label = NULL;
	(*data)->op = 0;
	(*data)->co = 0;
	(*data)->ls = 0;
	(*data)->n = 0;
	(*data)->func = NULL;
	(*data)->arg1 = NULL;
	(*data)->arg2 = NULL;
	(*data)->arg3 = NULL;
	(*data)->next = NULL;
}

static void		push_back(t_data **tmp, char *str, int i)
{
	while ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	if (!is_full((*tmp), i))
	{
		if (i == 1)
		{
			(*tmp)->func = ft_strdup(str);
			op_ls_co(str, &((*tmp)));
		}
		(i == 2) ? ((*tmp)->arg1 = ft_strdup(str)) : 0;
		(i == 3) ? ((*tmp)->arg2 = ft_strdup(str)) : 0;
		(i == 4) ? ((*tmp)->arg3 = ft_strdup(str)) : 0;
	}
	else
	{
		create_data(&((*tmp)->next));
		(i == 0) ? ((*tmp)->next->label = ft_strdup(str)) : 0;
		if (i == 1)
		{
			(*tmp)->next->func = ft_strdup(str);
			op_ls_co(str, &((*tmp)->next));
		}
	}
}

void			add_data(char *str, int i, t_name_comm *info)
{
	t_data	*tmp;

	if (!(info->data))
	{
		create_data(&(info->data));
		(i == 0) ? (info->data->label = ft_strdup(str)) : 0;
		if (i == 1)
		{
			info->data->func = ft_strdup(str);
			op_ls_co(str, &(info->data));
		}
	}
	else
	{
		tmp = info->data;
		push_back(&tmp, str, i);
	}
}
