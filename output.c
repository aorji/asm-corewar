/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 12:47:24 by aorji             #+#    #+#             */
/*   Updated: 2018/07/05 12:47:26 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// static int check_name(t_file_name **f_name, char *name)
// {
// 	t_file_name *tmp;
// 	t_file_name	*tmp1;

// 	if (!(*f_name))
// 	{
// 		(*f_name) = (t_file_name*)malloc(sizeof(t_file_name));
// 		(*f_name)->name = name;
// 		(*f_name)->next = NULL;
// 		return (0);
// 	}
// 	else
// 	{
// 		tmp1 = *f_name;
// 		while (tmp1)
// 		{
// 			if (!tmp1->next)
// 				tmp = tmp1;
// 			if (!(ft_strcmp(tmp1->name, name)))
// 				return (1);
// 			tmp1 = tmp1->next;
// 		}
// 		tmp->next = (t_file_name*)malloc(sizeof(t_file_name));
// 		tmp->next->name = name;
// 		tmp->next->next = NULL;
// 	}
// 	return (2);
// }


int print(char **av, int file)
{
	// int file;
	int n;
	char	*tmp;
	// t_file_name *f_name;

	// file = 0;
	// f_name = NULL;
	//data
	//
	// while (++file < ac)
	// {	
		// if (!ft_strcmp(av[file], "struct"))
		// {
		// 	while (info.data)
		// 	{
		// 		ft_putstr("--------------------\n");
		// 		ft_putstr("label = ");
		// 		ft_putstr(info.data->label);
		// 		write(1, "\n", 1);
		// 		ft_putstr("func = ");
		// 		ft_putstr(info.data->func);
		// 		write(1, "\n", 1);
		// 		ft_putstr("arg1 = ");
		// 		ft_putstr(info.data->arg1);
		// 		write(1, "\n", 1);
		// 		ft_putstr("arg2 = ");
		// 		ft_putstr(info.data->arg2);
		// 		write(1, "\n", 1);
		// 		ft_putstr("arg3 = ");
		// 		ft_putstr(info.data->arg3);
		// 		write(1, "\n", 1);
		// 		info.data = info.data->next;
		// 	}
		// 	continue;
		// }
		// if ((n = check_name(&f_name, av[file])) == 1)
		// 	continue;
		// if (n == 2)
		// 	ft_putstr(", ");
		//compiller
		n = ft_strlen(av[file]) - 1;
		while (av[file][n] && av[file][n] != '/')
			n--;
		tmp = ft_strsub(av[file], n + 1, ft_strlen(av[file]) - (n + 1) - 2);
		ft_putstr(OUTPUT);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		ft_putstr(".cor\n");
	// }
		// ft_putstr("\n");
	// free_name(&f_name);
	return (0);
}
