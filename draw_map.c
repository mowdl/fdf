/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:55 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/12 01:17:47 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	fdf_abs(float a)
{
	if (a < 0)
		return (-a);
	return a;
}

typedef struct t_line {
	float	ax;
	float	ay;
	float	bx;
	float	by;
} t_line;

void	draw_line(t_fdf *fdf, t_point a, t_point b)
{
	int		x;
	int		y;
	float	m;
	float	c;
	t_line	line;

	line.ax = a.x;
	line.ay = a.y;
	line.bx = b.x;
	line.by = b.y;

	m = (line.by - line.ay) / (line.bx - line.ax);
	c = line.ay - m * line.ax;
	x = line.ax;
	while (x < line.bx + 1)
	{
		y = line.ay;
		while (y < line.by + 1)
		{
			if (fdf_abs(y - (m * x + c)) < 0.5f)
			{
				set_pixel(&fdf->img_d, x, y, 0xFFFFFF);
			}
			y++;
		}
		x++;
	}
}

t_point	get_point(int i, int j)
{
	t_fdf	*fdf;

	fdf = get_fdf();
	return (fdf->map.points[i + j * fdf->map.w]);
}

void	draw_map(t_fdf *fdf)
{
	for (int j = 0; j < WIN_HEIGHT; j++)
	{
		for (int i = 0; i < WIN_WIDTH; i++) {
			set_pixel(&fdf->img_d, i, j, 0x0);
		}
	}
	for (int j = 10; j < fdf->map.h - 10; j++)
	{
		for (int i = 10; i < fdf->map.w - 10; i++) {
			draw_line(fdf, get_point(i, j), get_point(i+1, j+1));
		}
	}
}

void	set_pixel(t_image_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
