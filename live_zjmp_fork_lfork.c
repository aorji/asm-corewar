/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjmp_fork_lfork.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:57:24 by aorji             #+#    #+#             */
/*   Updated: 2018/07/02 15:57:25 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *arg1(char *line, t_name_comm *info, char *f_name)
{
	if (line[0] == DIRECT_CHAR)
		return (t_dir_arg2(line, info, f_name));
	else
		return (instract_error(info, f_name));
}

int	live_zjmp_fork_lfork(char *line, t_name_comm *info, char *f_name)
{
	if (ft_strncmp(line, "live", 4) && ft_strncmp(line, "zjmp", 4) 
		&& ft_strncmp(line, "fork", 4) && ft_strncmp(line, "lfork", 5))
		return (0);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	(info->in)++;
	if (!ft_strncmp(line, "lfork", 5))
	{
		line += 1;
		(info->index) += 1;
	}
	line += 4;
	(info->index) += 4;
	line = ws(line, info);
	line = arg1(line, info, f_name);
	if (!line)
		return (ERROR);
	return (1);
}
