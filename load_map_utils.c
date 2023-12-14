/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:01:39 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/14 21:02:39 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	int_from_char_hex(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
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
		point.color = 0;
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
