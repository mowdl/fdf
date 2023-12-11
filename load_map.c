/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:03:46 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/11 18:37:30 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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
	fdf->map_data.splited_lines = ft_lstmap(fdf->map_data.lines, split_line, del_with_free);
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

int	int_from_char_hex(char c)
{
	if (ft_isdigit(c))
		return (c - 0);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	fdf_err("Error in input\n");
	return (0);
}

t_point	parse_point(char *str, int x, int y)
{
	t_point	point;
	char	*comma;

	point.x = x;
	point.y = y;
	point.z = ft_atoi(str);
	comma = ft_strchr(str, ',');
	if (comma == NULL)
		point.color = 0x00ffffff;
	else if (comma[1] != '0' || comma[2] != 'x')
		fdf_err("Error in input\n");
	else
	{
		comma = comma + 3;
		comma[6] = '\0';
		while (*comma)
		{
			point.color = point.color * 16 + int_from_char_hex(*comma);
			comma++;
		}
	}
	return (point);
}

void	parse_points_arr(t_fdf *fdf)
{
	int		x;
	int		y;
	char	**arr;
	t_list	*line;

	line = fdf->map_data.splited_lines;
	y = 0;
	while (y < fdf->map.h)
	{
		arr = line->content;
		x = 0;
		while (x < fdf->map.w)
		{
			if (*arr == NULL)
				fdf_err("Error in input\n");
			fdf->map.points[x + y * fdf->map.w] = parse_point(*arr, x, y);
			arr++;
			x++;
		}
		line = line->next;
		y++;
	}
}

void	load_map(t_fdf *fdf)
{
	t_map_data *map_data = &fdf->map_data;

	map_data->fd = open(map_data->file_path, O_RDWR);
	if (map_data->fd == -1)
		fdf_err("Could not open the file\n");
	load_lines(fdf);
	split_lines(fdf);
	init_map(fdf);
	parse_points_arr(fdf);
}
