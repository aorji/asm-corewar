/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:24:30 by aorji             #+#    #+#             */
/*   Updated: 2018/06/29 18:24:36 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *arg2(char *line, t_name_comm *info, char *f_name)
{
	int n;
	char *str;
	int i = 0;
	
	if (line[i] == ':')
		i++;
	while (line[i] && ft_isalnum(line[i]))
		i++;
	str = ft_strsub(line, 0, i);
	add_data(str, 3, info);
	ft_strdel(&str);
	if (line[0] == LABEL_CHAR)
		return (label_arg2(line, info, f_name));
	else if (line[0] == LABEL_CHAR)
		return (label_arg2(line, info, f_name));
	else if (line[0] == 'r')
		return (t_reg_arg2(line, info, f_name));
	else
	{
		if ((n = atoi(line)) != 0 || (line[0] == 48
			&& (line[1] == ' ' || line[1] == '\t' || line[1] == '\0')))
			return (t_int_arg2(line, info, f_name));
		else
			return (instract_error(info, f_name));
	}
}

static char *arg1(char *line, t_name_comm *info, char *f_name)
{
	int i = 0;
	char *str;
	
	while (line[i] && line[i] != ',')
		i++;
	str = ft_strsub(line, 0, i);
	add_data(str, 2, info);
	ft_strdel(&str);
	if (line[0] == 'r')
		return (t_reg_arg1(line, info, f_name));
	else
		return (instract_error(info, f_name));
}

int	st(char *line, t_name_comm *info, char *f_name)
{
	char *str;

	if (ft_strncmp(line, "st", 2))
		return (0);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	str = ft_strsub(line, 0, 2);
	add_data(str, 1, info);
	ft_strdel(&str);
	(info->in)++;
	line += 2;
	(info->index) += 2;
	line = ws(line, info);
	line = arg1(line, info, f_name);
	if (!line)
		return (ERROR);
	line = ws(line, info);
	line = arg2(line, info, f_name);
	if (!line)
		return (ERROR);
	return (1);
}
