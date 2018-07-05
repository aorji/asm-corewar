/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 11:15:55 by nrepak            #+#    #+#             */
/*   Updated: 2018/06/26 11:56:20 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	usage_check(char **av, int fd, int i)
{
	int len;

	if (fd == ERROR)
		return (usage_error(USAGE1, av[i]));
	len = ft_strlen(av[i]);
	if (!(av[i][len - 1] == 's' && av[i][len - 2] == '.'))
		return (usage_error(USAGE, NULL));
	return (0);
}

static int	label_check(t_name_comm info, char *f_name)
{
	while (info.label)
	{
		if (!((info.label)->found))
			return (label_error((info.label)->name, (info.label)->x, (info.label)->y, f_name));
		(info.label) = (info.label)->next;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_name_comm info;
	int file;
	int error;

	if (ac < 2)
		return (usage_error(USAGE, NULL));
	error = 0;
	file = 1;
	while (file < ac)
	{
		info = (t_name_comm){0, 0, 0, 0, 0, 0, 0, 0, NULL};
		info.fd = open(av[file], O_RDONLY);
		if (usage_check(av, info.fd, file) == ERROR)
			error = 1;
		else if (file_check(&info, av[file]) == ERROR)
			error = 1;
		else if (label_check(info, av[file]) == ERROR)
			error = 1;
		file++;
	}
	if (!error)
		print(av, ac);
	return (0);
}
