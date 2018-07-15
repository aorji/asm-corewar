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

int	main(int ac, char **av)
{
	int			file;
	int			error;
	t_file_name	*f_name;

	f_name = NULL;
	if (ac < 2)
		return (usage_error(USAGE, NULL));
	error = 0;
	file = 0;
	while (++file < ac)
	{
		error = validation(&f_name, file, av);
		if (error == -1)
			file++;
		if (error == 1)
			break ;
	}
	free_name(&f_name);
	system("leaks -q asm");
	return (0);
}
