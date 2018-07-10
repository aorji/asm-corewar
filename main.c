/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrepak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 11:15:55 by nrepak            #+#    #+#             */
/*   Updated: 2018/06/26 11:56:20 by nrepak           ###   ########.fr       */
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
			if (!tmp1->next)
				tmp = tmp1;
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

static void free_name(t_file_name **f_name)
{
	t_file_name *fr;

	while ((*f_name))
	{
		fr = (*f_name);
		(*f_name) = (*f_name)->next;
		free(fr);
		fr->name = NULL;
	}
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
			return (label_error((info.label)->name, (info.label)->x, (info.label)->y, f_name));
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

static void free_lists(t_name_comm *info)
{
	t_label *tmp;
	t_data *tmp1;

	while (info->label)
	{
		tmp = info->label;
		info->label = info->label->next;
		free(tmp->name);
		free(tmp);
		tmp = NULL;
	}
	while (info->data)
	{
		tmp1 = info->data;
		info->data = info->data->next;
		free(tmp1->label);
		free(tmp1->func);
		free(tmp1->arg1);
		free(tmp1->arg2);
		free(tmp1->arg3);
		free(tmp1);
		tmp1 = NULL;
	}
	free(info->name_comm.name);
	free(info->name_comm.comment);
}

int			main(int ac, char **av)
{
	t_name_comm info;
	int file;
	int error;
	t_data *tmp;
	int n;
	t_file_name *f_name;
	f_name = NULL;

	if (ac < 2)
		return (usage_error(USAGE, NULL));
	error = 0;
	file = 0;
	while (++file < ac)
	{
		if ((n = check_name(&f_name, av[file])) == 1)
			continue;
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
		if (!error)
			print(av, file, &info);
		if (!error && av[file + 1] && !ft_strcmp(av[file + 1], "-struct"))
		{
			tmp = info.data;
			while (tmp)
			{
				ft_putstr("--------------------\n");
				ft_putstr("label = ");
				ft_putstr(tmp->label);
				write(1, "\n", 1);
				ft_putstr("func = ");
				ft_putstr(tmp->func);
				write(1, "\n", 1);
				ft_putstr("op = ");
				ft_putnbr_fd(tmp->op, 1);
				write(1, "\n", 1);
				ft_putstr("co = ");
				ft_putnbr_fd(tmp->co, 1);
				write(1, "\n", 1);
				ft_putstr("ls = ");
				ft_putnbr_fd(tmp->ls, 1);
				write(1, "\n", 1);
				ft_putstr("n = ");
				ft_putnbr_fd(tmp->n, 1);
				write(1, "\n", 1);
				ft_putstr("arg1 = ");
				ft_putstr(tmp->arg1);
				write(1, "\n", 1);
				ft_putstr("arg2 = ");
				ft_putstr(tmp->arg2);
				write(1, "\n", 1);
				ft_putstr("arg3 = ");
				ft_putstr(tmp->arg3);
				write(1, "\n", 1);
				tmp = tmp->next;
			}
			write(1, "\n", 1);
			file++;
		}
		free_lists(&info);
		if (error)
			break;
	}
	free_name(&f_name);
	system("leaks -q asm");
	return (0);
}
