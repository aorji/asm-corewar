/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:24:30 by aorji             #+#    #+#             */
/*   Updated: 2018/06/29 18:24:36 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	add_label(char *line, t_name_comm *info)
{
	int i = 0;
	// t_list *tmp;

	while (line[i] && line[i] != ' ' && line[i] != '\t')
	{
		if (*line == '\t')
			add_tab(info);
		i++;
	}
	// tmp = info->label;
	while (info->label)
		info->label = info->label->next;
	info->label = ft_lstnew(ft_strsub(line, 0, i), i);
	// info->label = tmp;
	// printf("%s\n", info->label->content);
	return (i);
}

static char *arg2(char *line, t_name_comm *info)
{
	int tr;
	int n;
	int d_len;

	if (!line)
		return (NULL);
	if (line[0] == ':')
	{
		info->index++;
		line++;
		n = add_label(line, info); //!!!!!!!!!!!!!!!!!!!!!! lists
		info->index += n;
		line += n;
		line = ws(line, info);
		if ((tr = trash(line, 0)) != -1)
		{
			info->index += tr;
			trash_error(*info, line, 0);
			return (NULL);
		}
		return (line);
	}
	else if (line[0] == 'r')
	{
		line++;
		(info->index)++;
		d_len = ft_number_size((n = atoi(line)));
		if (n <= REG_NUMBER && n >= 1)
		{
			line += d_len;
			info->index += d_len;
			line = ws(line, info);
			if ((tr = trash(line, 0)) != -1)
			{
				info->index += tr;
				trash_error(*info, line, 0);
				return (NULL);
			}
			return (line);
		}
		else
		{
			trash_error(*info, line, 0);
			return (NULL);
		}
	}
	else
	{
		if ((n = atoi(line)) != 0 || (line[0] == 0 && (line[1] == ' ' || line[1] == '\t')))
		{
			n = ft_number_size(n);
			line += n;
			info->index += n;
			line = ws(line, info);
			if ((tr = trash(line, 0)) != -1)
			{
				info->index += tr;
				trash_error(*info, line, 0);
				return (NULL);
			}
			return (line);
		}
		else
		{
			st_error(2);
			return (NULL);
		}
	}
	return (NULL);
}

static char *arg1(char *line, t_name_comm *info)
{
	int n;
	int	d_len;

	if (line[0] == 'r')
	{
		line++;
		(info->index)++;
		d_len = ft_number_size((n = atoi(line)));
		if (n <= REG_NUMBER && n >= 1)
		{
			line += d_len;
			info->index += d_len;
			line = ws(line, info);
			if (*line == ',')
			{
				line++;
				(info->index)++;
			}
			else
				return (sep_error(info));
		}
		else
		{
			trash_error(*info, line, 0);
			return (NULL);
		}
	}
	else
		return (st_error(1));
	return (ws(line, info));
}

int	st_check(char *line, t_name_comm *info, char *f_name)
{
	if (ft_strncmp(line, "st", 2))
		return (1);
	if (info->count != 2)
		return (syntax_error(SYNT_ERROR, f_name));
	line += 2;
	(info->index) += 2;
	line = ws(line, info);
	line = arg1(line, info);
	line = arg2(line, info);
	if (!line)
		return (ERROR);
	return (1);
}
