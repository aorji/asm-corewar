/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 14:38:44 by aorji             #+#    #+#             */
/*   Updated: 2018/07/09 14:38:46 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void check_arg(char *arg, int ls, int *i)
{
	if (!arg)
		return ;
	if (arg[0] == 'r')
		(*i)++;
	else if (arg[0] == '%')
		(*i) += ls;
	else
		(*i) += 2;
}


int	bot_size(t_name_comm *info)
{
	t_data *data;
	int i;

	data = info->data;
	while (data->next)
	{
		i = 1;
		if (data->co)
			i++;
		check_arg(data->arg1, data->ls, &i);
		check_arg(data->arg2, data->ls, &i);
		check_arg(data->arg3, data->ls, &i);
		data->next->n = i + data->n;
		data = data->next;
	}
	i = 1;
	if (data->co)
		i++;
	check_arg(data->arg1, data->ls, &i);
	check_arg(data->arg2, data->ls, &i);
	check_arg(data->arg3, data->ls, &i);
	return (i + data->n);
}
