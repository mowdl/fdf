/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:03:46 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/06 23:29:41 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

t_list	*load_lines(int file_name);
int	arr_len(char **arr);

static char	**free_arr(char **arr)
{
	size_t	i;
	size_t	len;

	len = arr_len(arr);
	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	arr_len(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		i++;
	return (i);
}


void	*load_map(int fd, t_map *map)
{
	t_list	*lines;
	t_list	*tmp;
	char	**arr;

	lines = load_lines(fd);
	if (lines == 0)
		return (NULL);
	map->h = ft_lstsize(lines);
	tmp = lines;
	arr = ft_split(tmp->content, ' ');
	if (arr == NULL)
		return (NULL);
	map->w = arr_len(arr);
	free_arr(arr);
	map->m = malloc(sizeof(int)* map->h * map->w);
	if (map->m == NULL)
		return (NULL);
	int j = 0;
	while(tmp)
	{
		arr = ft_split(tmp->content, ' ');
		if (arr == NULL)
			return (NULL);
		int i = 0;
		while (i < map->w)
		{
			map->m[i + j * map->w] = ft_atoi(arr[i]);
			i++;
		}
		free_arr(arr);
		tmp = tmp->next;
		j++;
	}
	return (map);
}

t_list	*load_lines(int fd)
{
	char	*line;
	t_list	*lines;

	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	return (lines);
}
