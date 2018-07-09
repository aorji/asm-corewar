/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 14:40:29 by aorji             #+#    #+#             */
/*   Updated: 2018/07/09 14:40:30 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// static int find_label(t_data *data, char *name)
// {
// 	while (data)
// 	{
// 		if (data->label && !ft_strcmp(data->label, name))
// 			return (data->n);
// 		data = data->next;
// 	}
// 	return (-1);
// }

static void push_data(int fd, t_data *data)
{
	char *str;

	str = ft_itoa_base(15369203, 16);
	ft_putstr_fd("00", fd);
	ft_putstr_fd(str, fd);
	str = ft_itoa_base(data->op, 16);
	if (ft_strlen(str) == 1)
		ft_putstr_fd("0", fd);
	ft_putstr_fd(str, fd);
}


void	compiler(t_name_comm *info, char *name)
{
	int size;
	int fd;
	char *tmp;

	size = bot_size(info);
	tmp = ft_strjoin(name, ".cor");
	fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	push_data(fd, info->data);
}
