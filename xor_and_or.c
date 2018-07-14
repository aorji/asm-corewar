/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_and_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 13:59:40 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 13:59:41 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *arg3(char *line, t_name_comm *info, char *f_name)
{
	int i = 0;
	char *str;
	
	while (line[i] && ft_isalnum(line[i]))
		i++;
	str = ft_strsub(line, 0, i);
	add_data(str, 4, info);
	ft_strdel(&str);
	if (line[0] == 'r')
		return (t_reg_arg2(line, info, f_name));
	else if (line[0] == LABEL_CHAR)
		return (label_arg2(line, info, f_name));
	else
		return (instract_error(info, f_name));
}

static char *arg2(char *line, t_name_comm *info, char *f_name)
{
	int n;
	int i = 0;
	char *str;
	
	while (line[i] && line[i] != ',')
		i++;
	str = ft_strsub(line, 0, i);
	add_data(str, 3, info);
	ft_strdel(&str);
	if (line[0] == 'r')
		return (t_reg_arg1(line, info, f_name));
	else if (line[0] == LABEL_CHAR)
		return (label_arg1(line, info, f_name));
	else if ((n = atoi(line)) != 0 || (line[0] == '0' 
		&& (line[1] == ' ' || line[1] == '\t' || line[1] == ',')))
		return (t_int_arg1(line, info, f_name));
	else if (line[0] == '%')
		return (t_dir_arg1(line, info, f_name));
	else
		return (instract_error(info, f_name));
}

static char *arg1(char *line, t_name_comm *info, char *f_name)
{
	int n;
	int i = 0;
	char *str;
	
	while (line[i] && line[i] != ',')
		i++;
	str = ft_strsub(line, 0, i);
	add_data(str, 2, info);
	ft_strdel(&str);
	if (line[0] == 'r')
		return (t_reg_arg1(line, info, f_name));
	else if (line[0] == LABEL_CHAR)
		return (label_arg1(line, info, f_name));
	else if ((n = atoi(line)) != 0 || (line[0] == '0' 
		&& (line[1] == ' ' || line[1] == '\t' || line[1] == ',')))
		return (t_int_arg1(line, info, f_name));
	else if (line[0] == '%')
		return (t_dir_arg1(line, info, f_name));
	else
		return (instract_error(info, f_name));
}

int	xor_and_or(char *line, t_name_comm *info, char *f_name)
{
	if (ft_strncmp(line, "xor", 3) && ft_strncmp(line, "or", 2)
		&& ft_strncmp(line, "and", 3))
		return (0);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	(info->in)++;
	if (!ft_strncmp(line, "or", 2))
		add_func(info, &line, 2, 1);
	else
		add_func(info, &line, 3, 1);
	line = ws(line, info);
	line = arg1(line, info, f_name);
	if (!line)
		return (ERROR);
	line = ws(line, info);
	line = arg2(line, info, f_name);
	if (!line)
		return (ERROR);
	line = ws(line, info);
	line = arg3(line, info, f_name);
	if (!line)
		return (ERROR);
	return (1);
}
