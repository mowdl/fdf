/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:23:36 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/06 22:02:12 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	fdf_abs(float a)
{
	if (a < 0)
		return (-a);
	return a;
}

void	draw_line(t_image_data *img_data, t_line line)
{
	int		x;
	int		y;
	float	m;
	float	c;

	m = (line.b.y - line.a.y) / (line.b.x - line.a.x);
	c = line.a.y - m * line.a.x;
	x = line.a.x;
	while (x < line.b.x + 1)
	{
		y = line.a.y;
		while (y < line.b.y + 1)
		{
			if (fdf_abs(y - (m * x + c)) < 1.0f)
			{
				my_mlx_pixel_put(img_data, x, y, floats_to_color(0, 1, 1, 1));
			}
			y++;
		}
		x++;
	}
}
