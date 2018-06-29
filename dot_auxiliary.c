/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_auxiliary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 21:07:28 by aorji             #+#    #+#             */
/*   Updated: 2018/06/28 21:07:31 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int close_quatation(char *line, int i)
{
	while (line[i] != '\"' && line[i])
		i++;
	if (line[i] == '\"')
		return (i);
	return (-1);
}

int open_quotation(char *line, int *i, int *column) 
{
	while ((line[*i] != ' ' && line[*i] != '\t') && line[*i])
		(*i)++;
	while ((line[*i] == ' ' || line[*i] == '\t') && line[*i])
		(*i)++;
	(*column) = *i + 2;
	if (line[(*i)++] != '\"')
		return (-1);
	return (*i);
}

int trash(char *line, int q)
{
	int i;

	i = 1;
	while (line[q])
	{
		if (line[q] != ' ' && line[q] != '\t')
			return (i);
		q++;
		i++;
	}
	return (0);
}
