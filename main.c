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

static int	usage_check(int ac, char **av, int fd, int i)
{
	int len;

	if (ac < 2)
		return (usage_error(USAGE, NULL));
	if (fd == -1)
		return (usage_error(USAGE1, av[i]));
	len = ft_strlen(av[i]);
	if (!(av[i][len - 1] == 's' && av[i][len - 2] == '.'))
		return (usage_error(USAGE, NULL));
	return (0);
}

int			main(int ac, char **av)
{
	t_name_comm info;
	int file;
	int error;

	error = 0;
	file = 1;
	while (file < ac)
	{	
		info = (t_name_comm){0, 0, 0, 0, 0, 0, 0, NULL};
		info.fd = open(av[file], O_RDONLY);
		if (usage_check(ac, av, info.fd, file) == ERROR)
			error = 1;
		else if (file_check(&info, av[file]) == ERROR)
			error = 1;
		printf("%s ", "labels:");
		while (info.label)
		{
			printf("%s; ", (info.label)->name);
			(info.label) = (info.label)->next;
		}
		printf("\n");
		file++;
	}
	if (!error)
		ft_putstr("Writing output program\n");
	return (0);
}
