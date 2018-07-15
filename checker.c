/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 13:43:40 by nrepak            #+#    #+#             */
/*   Updated: 2018/07/13 15:44:20 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	char_cmp(char *str, char *str1, int k, int i)
{
	if (str[0] != str1[0])
	{
		if (!(k % 16))
			ft_printf("line == %d: ", i - 1);
		else
			ft_printf("line == %d: ", i);
		ft_printf("%x != %x\n", str[0], str1[0]);
		return (1);
	}
	return (0);
}

static int ft_read(int fd, int fd1, int k, int i)
{
	char str[2];
	char str1[2];
	int a;
	int b;
	int error;

	error = 0;
	while (((a = read(fd, str, 1)) >= 0) && ((b = read(fd1, str1, 1)) >= 0))
	{ 
		k++;
		if (!(k % 16))
			i++;
		if (!a && !b && !error)
			return (ft_printf("%s\n", "OK"));
		else if (!a && !b)
			return (ft_printf("%s\n", "ERROR"));
		str[a] = '\0';
		str1[b] = '\0';
		error = char_cmp(str, str1, k, i);
	}
	if (error)
		return (ft_printf("%s\n", "ERROR"));
	if (a == -1 || b == -1)
		return (ft_printf("%s\n", "An error occurred in the read."));
	return (0);
}

int		main(int ac, char **av)
{
	int fd;
	int fd1;

	if (ac != 3)
		return (ft_printf("%s\n",
			"Usage: ./checker file_name1[.cor] file_name2[.cor]"));
	fd = open(av[1], O_RDONLY);
	fd1 = open(av[2], O_RDONLY);
	if (ft_read(fd, fd1, 0, 1))
		return (0);
	write (1, "OK\n", 3);
	return (0);
}
