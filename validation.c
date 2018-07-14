/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 02:27:21 by nrepak            #+#    #+#             */
/*   Updated: 2018/07/14 02:27:24 by nrepak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int check_name(t_file_name **f_name, char *name)
{
	t_file_name *tmp;
	t_file_name	*tmp1;

	if (!(*f_name))
	{
		(*f_name) = (t_file_name*)malloc(sizeof(t_file_name));
		(*f_name)->name = name;
		(*f_name)->next = NULL;
		return (0);
	}
	else
	{
		tmp1 = *f_name;
		while (tmp1)
		{
			(!tmp1->next) ? tmp = tmp1 : 0;
			if (!(ft_strcmp(tmp1->name, name)))
				return (1);
			tmp1 = tmp1->next;
		}
		tmp->next = (t_file_name*)malloc(sizeof(t_file_name));
		tmp->next->name = name;
		tmp->next->next = NULL;
	}
	return (2);
}

static int	usage_check(char **av, int fd, int i)
{
	int len;

	if (fd == ERROR)
		return (usage_error(USAGE1, av[i]));
	len = ft_strlen(av[i]);
	if (!(av[i][len - 1] == 's' && av[i][len - 2] == '.'))
		return (usage_error(USAGE, NULL));
	return (0);
}

static int	label_check(t_name_comm info, char *f_name)
{
	while (info.label)
	{
		if (!((info.label)->found))
			return (label_error((info.label)->name,
				(info.label)->x, (info.label)->y, f_name));
		(info.label) = (info.label)->next;
	}
	return (0);
}

static	int lenth_check(t_name_comm info)
{
	if (ft_strlen(info.name_comm.name) > PROG_NAME_LENGTH)
		return (name_lenth_error());
	if (ft_strlen(info.name_comm.comment) > COMMENT_LENGTH)
		return (comment_lenth_error());
	return (0);
}

int validation(t_file_name **f_name, int file, char **av)
{
	int error;
	t_name_comm info;

	error = 0;
	if (check_name(f_name, av[file]) == 1)
		return (0);
	info = (t_name_comm){0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, {NULL, NULL}};
	info.fd = open(av[file], O_RDONLY);
	if (usage_check(av, info.fd, file) == ERROR)
		error = 1;
	else if (file_check(&info, av[file]) == ERROR)
		error = 1;
	else if (label_check(info, av[file]) == ERROR)
		error = 1;
	else if (lenth_check(info) == ERROR)
		error = 1;
	(!error) ? print(av, file, &info) : 0;
	if (!error && av[file + 1] && !ft_strcmp(av[file + 1], "-struct"))
	{
		print_struct(info.data);
		free_lists(&info);
		return (-1);
	}
	free_lists(&info);
	return (error);
}
