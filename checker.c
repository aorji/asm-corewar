/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 13:43:40 by nrepak            #+#    #+#             */
/*   Updated: 2018/07/13 13:43:51 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int ft_read(int fd, int fd1)
{
	char str[2];
	char str1[2];
	int a;
	int b;

	while (((a = read(fd, str, 1)) >= 0) && ((b = read(fd1, str1, 1)) >= 0))
	{
		if (!a && !b)
		{
			write (1, "OK\n", 3);
			return (0);
		}
		str[a] = '\0';
		str1[b] = '\0';
		if (str[0] != str1[0])
		{
			printf("%x", str[0]);
			printf(" != %x\n", str1[0]);
			write (2, "ERROR\n", 6);
			return (0);
		}
	}
	if (a == -1 || b == -1)
	{
		write(2, "An error occurred in the read.\n", 31);
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	int fd;
	int fd1;

	if (ac != 3)
	{
		write(2, "Usage: ./checker file_name1[.cor] file_name2[.cor]\n", 51);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	fd1 = open(av[2], O_RDONLY);
	if (!ft_read(fd, fd1))
		return (0);
	write (1, "OK\n", 3);
	return (0);
}