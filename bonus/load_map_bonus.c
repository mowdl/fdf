/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:03:46 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/13 02:59:22 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <fcntl.h>

void	load_lines(t_fdf *fdf)
{
	char	*line;
	t_list	*tmp;

	line = get_next_line(fdf->map_data.fd);
	if (line == NULL)
		fdf_err("Error while reading from file\n");
	while (line)
	{
		tmp = ft_lstnew(line);
		if (tmp == NULL)
			fdf_err("Memory error while reading from file\n");
		ft_lstadd_back(&fdf->map_data.lines, tmp);
		line = get_next_line(fdf->map_data.fd);
	}
}

void	*split_line(void	*content)
{
	char	**arr;

	arr = ft_split(content, ' ');
	if (arr == NULL)
		fdf_err("Memory error while parsing the file\n");
	return (arr);
}

void	split_lines(t_fdf *fdf)
{
	fdf->map_data.splited_lines = ft_lstmap(fdf->map_data.lines,
			split_line, del_with_free);
	if (fdf->map_data.splited_lines == NULL)
		fdf_err("Memory error while parsing the file\n");
}

void	init_map(t_fdf *fdf)
{
	int		h;
	int		w;
	char	**arr;
	t_point	*points;

	h = ft_lstsize(fdf->map_data.lines);
	arr = fdf->map_data.splited_lines->content;
	w = 0;
	while (*arr && **arr != '\n')
	{
		w++;
		arr++;
	}
	if (h * w == 0)
		fdf_err("Error in the input\n");
	points = malloc(sizeof(t_point) * h * w);
	if (points == NULL)
		fdf_err("Memory error while parsing file\n");
	fdf->map.points = points;
	fdf->map.h = h;
	fdf->map.w = w;
}

void	load_map(t_fdf *fdf)
{
	t_map_data	*map_data;

	map_data = &fdf->map_data;
	map_data->fd = open(map_data->file_path, O_RDWR);
	if (map_data->fd == -1)
		fdf_err("Could not open the file\n");
	load_lines(fdf);
	split_lines(fdf);
	init_map(fdf);
	parse_points_arr(fdf);
}
