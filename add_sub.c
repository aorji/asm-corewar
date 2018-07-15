/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:59:09 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 15:59:10 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*arg3(char *line, t_name_comm *info, char *f_name)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '-'))
		i++;
	str = ft_strsub(line, 0, i);
	add_data(str, 4, info);
	ft_strdel(&str);
	if (line[0] == 'r')
		return (t_reg_arg2(line, info, f_name));
	else
		return (instract_error(info, f_name));
}

static char		*arg2(char *line, t_name_comm *info, char *f_name)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	str = ft_strsub(line, 0, i);
	add_data(str, 3, info);
	ft_strdel(&str);
	if (line[0] == 'r')
		return (t_reg_arg1(line, info, f_name));
	else
		return (instract_error(info, f_name));
}

static char		*arg1(char *line, t_name_comm *info, char *f_name)
{
	char	*str;
	int		i;

	i = 0;
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

int				add_sub(char *line, t_name_comm *info, char *f_name)
{
	if (ft_strncmp(line, "add", 3) && ft_strncmp(line, "sub", 3))
		return (0);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
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
