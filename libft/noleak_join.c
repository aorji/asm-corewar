/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noleak_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:19:00 by aorji             #+#    #+#             */
/*   Updated: 2018/07/07 14:19:06 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*noleak_strjoin(char const *s1, char const *s2, char **to_free)
{
	char	*new;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (0);
	while (*s1)
	{
		new[i++] = *s1++;
	}
	while (*s2)
	{
		new[i++] = *s2++;
	}
	new[i] = '\0';
	ft_strdel(to_free);
	return (new);
}
