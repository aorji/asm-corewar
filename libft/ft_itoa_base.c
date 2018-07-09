/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:16:30 by aorji             #+#    #+#             */
/*   Updated: 2018/07/09 16:18:29 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(uintmax_t n, unsigned int b)
{
	int	i;

	i = 1;
	while (n / b)
	{
		n /= b;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(uintmax_t value, unsigned int base)
{
	int			len;
	uintmax_t	n;
	char		*str;

	len = ft_len(value, base);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	len--;
	while (value >= base)
	{
		n = value;
		value /= base;
		n -= value * base;
		if (n >= 10 && n <= base)
			str[len] = n + 87;
		else
			str[len] = n + 48;
		len--;
	}
	if (value >= 10 && value < base)
		str[len] = (value + 87);
	if (value < 10)
		str[len] = value + 48;
	return (str);
}
