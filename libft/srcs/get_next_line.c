/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:43:01 by tjose             #+#    #+#             */
/*   Updated: 2017/02/21 14:26:23 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_file(t_files **dest, int fd)
{
	t_files *temp;

	temp = malloc(sizeof(t_files));
	if (!temp)
	{
		temp = NULL;
		return ;
	}
	if (!(temp->leftover = malloc(BUFF_SIZE + 1)))
	{
		temp = NULL;
		return ;
	}
	ft_strclr(temp->leftover);
	temp->fd = fd;
	temp->next = *dest;
	*dest = temp;
}

int		handle_read(t_files **files, char **all_buffs, char *buff)
{
	int		i;
	int		n_flag;
	char	*temp;

	i = -1;
	n_flag = 0;
	while (buff[++i])
	{
		if (buff[i] == '\n')
		{
			buff[i] = '\0';
			if (i + 1 < BUFF_SIZE)
				(*files)->leftover =
					ft_strcpy((*files)->leftover, &buff[i + 1]);
			n_flag = 1;
			break ;
		}
	}
	if (!(temp = ft_strjoin(*all_buffs, buff)))
		return (-1);
	free(*all_buffs);
	*all_buffs = temp;
	return (n_flag);
}

int		read_buffs(t_files **files, char **all_buffs,
		char **line, t_files **head)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	int		flag;

	while ((ret = read((*files)->fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		flag = handle_read(files, all_buffs, buff);
		if (flag > 0)
			break ;
		else if (flag < 0)
			return (-1);
	}
	if (!(*line = ft_strdup(*all_buffs)))
		return (-1);
	if (!ret && !*line[0])
		return (0);
	*files = *head;
	return (1);
}

int		get_buffs(t_files **files, char **all_buffs,
		char **line, t_files **head)
{
	int		i;

	i = -1;
	if ((*files)->leftover[0])
	{
		free(*all_buffs);
		if (!(*all_buffs = ft_strdup((*files)->leftover)))
			return (-1);
		ft_strclr((*files)->leftover);
		while ((*all_buffs)[++i])
		{
			if ((*all_buffs)[i] == '\n')
			{
				(*all_buffs)[i] = '\0';
				(*files)->leftover =
					ft_strcpy((*files)->leftover, &(*all_buffs)[++i]);
				*files = *head;
				if (!(*line = ft_strdup(*all_buffs)))
					return (-1);
				return (1);
			}
		}
	}
	return (read_buffs(files, all_buffs, line, head));
}

int		get_next_line(const int fd, char **line)
{
	static t_files	*files;
	char			*all_buffs;
	t_files			*head;

	head = files;
	if (fd < 0 || !(all_buffs = ft_strnew(1)))
		return (-1);
	while (files)
	{
		if (files->fd == fd)
			break ;
		files = files->next;
	}
	if (!files)
	{
		files = head;
		add_file(&files, fd);
		if (!files)
			return (-1);
		head = files;
	}
	return (get_buffs(&files, &all_buffs, line, &head));
}
