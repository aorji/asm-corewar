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
	int i;
	int error;

	error = 0;
	i = 1;
	while (i < ac)
	{	
		info = (t_name_comm){0, 0, 0, 0, 0, 0, 0};
		info.fd = open(av[i], O_RDONLY); 
		if (usage_check(ac, av, info.fd, i) == USAGE_ERROR)
			return (0);
		if (file_check(info.fd, &info, av[i]) == USAGE_ERROR)
		{
			error = 1;
			i++;
			continue;
		}
		//if (!error)
			//asm
		close(info.fd);
		i++;
	}
	if (!error)
		ft_putstr("NO ERROR YET\n");
	return (0);
}
