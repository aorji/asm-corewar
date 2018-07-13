/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 21:44:12 by aorji             #+#    #+#             */
/*   Updated: 2018/07/10 21:44:14 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_struct(t_data *data)
{
	t_data *tmp;

	tmp = data;
	while (tmp)
	{
		ft_printf("%s%s\n", "--------------------\nlabel = ", tmp->label);
		ft_printf("%s%s\n%s%d\n", "func = ", tmp->func, "op = ", tmp->op);
		ft_printf("%s%d\n%s%d\n", "co = ", tmp->co, "ls = ", tmp->ls);
		ft_printf("%s%d\n%s%s\n", "n = ", tmp->n, "arg1 = ", tmp->arg1);
		ft_printf("%s%s\n%s%s\n", "arg2 = ", tmp->arg2, "arg3 = ", tmp->arg3);
		tmp = tmp->next;
	}
	write(1, "\n", 1);
}
