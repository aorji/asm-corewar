/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 21:52:18 by aorji             #+#    #+#             */
/*   Updated: 2018/07/10 21:52:19 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_name(t_file_name **f_name)
{
	t_file_name *fr;

	while ((*f_name))
	{
		fr = (*f_name);
		(*f_name) = (*f_name)->next;
		free(fr);
		fr->name = NULL;
	}
}

void	free_lists(t_name_comm *info)
{
	t_label	*tmp;
	t_data	*tmp1;

	while (info->label)
	{
		tmp = info->label;
		info->label = info->label->next;
		free(tmp->name);
		free(tmp);
		tmp = NULL;
	}
	while (info->data)
	{
		tmp1 = info->data;
		info->data = info->data->next;
		free(tmp1->label);
		free(tmp1->func);
		free(tmp1->arg1);
		free(tmp1->arg2);
		free(tmp1->arg3);
		free(tmp1);
		tmp1 = NULL;
	}
	free(info->name_comm.name);
	free(info->name_comm.comment);
}
