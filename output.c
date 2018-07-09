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

int print(char **av, int file)
{
	int n;
	char	*tmp;
		//compiller
	n = ft_strlen(av[file]) - 1;
	while (av[file][n] && av[file][n] != '/')
		n--;
	tmp = ft_strsub(av[file], n + 1, ft_strlen(av[file]) - (n + 1) - 2);
	ft_putstr(OUTPUT);
	ft_putstr(tmp);
	ft_strdel(&tmp);
	ft_putstr(".cor\n");
	return (0);
}
