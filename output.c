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

static int check_name(t_file_name **f_name, char *name)
{
	t_file_name *tmp;
	t_file_name	*tmp1;

	if (!(*f_name))
	{
		(*f_name) = (t_file_name*)malloc(sizeof(t_file_name));
		(*f_name)->name = name;
		(*f_name)->next = NULL;
		return (0);
	}
	else
	{
		tmp1 = *f_name;
		while (tmp1)
		{
			if (!tmp1->next)
				tmp = tmp1;
			if (!(ft_strcmp(tmp1->name, name)))
				return (1);
			tmp1 = tmp1->next;
		}
		tmp->next = (t_file_name*)malloc(sizeof(t_file_name));
		tmp->next->name = name;
		tmp->next->next = NULL;
	}
	return (2);
}

static void free_name(t_file_name **f_name)
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

int print(char **av, int ac)
{
	int file;
	int n;
	char	*tmp;
	t_file_name *f_name;

	file = 0;
	f_name = NULL;
	ft_putstr(OUTPUT);
	while (++file < ac)
	{	
		if ((n = check_name(&f_name, av[file])) == 1)
			continue;
		if (n == 2)
			ft_putstr(", ");
		//compiller
		n = ft_strlen(av[file]) - 1;
		while (av[file][n] && av[file][n] != '/')
			n--;
		tmp = ft_strsub(av[file], n + 1, ft_strlen(av[file]) - (n + 1) - 2);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		ft_putstr(".cor");
	}
	ft_putstr("\n");
	free_name(&f_name);
	return (0);
}
