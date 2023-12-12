/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:55 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/12 17:22:45 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_points(t_point *a, t_point *b)
{
	t_point tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	draw_point(t_fdf *fdf, t_point a, t_point b, t_point p)
{
	set_pixel(&fdf->img_d, p.x, p.y, (a.color + b.color) / 2);
}

void	draw_line_vertical(t_fdf *fdf, t_point a, t_point b)
{
	t_point	p;
	int		sign;

	if (a.y > b.y)
		sign = -1;
	else
		sign = 1;
	p = a;
	while (p.y != b.y)
	{
		draw_point(fdf, a, b, p);
		p.y += sign;
	}
}

void	draw_line_horizental(t_fdf *fdf, t_point a, t_point b)
{
	t_point	p;

	p = a;
	while (p.x != b.x)
	{
		draw_point(fdf, a, b, p);
		p.x++;
	}
}

void	draw_line_positive(t_fdf *fdf, t_point a, t_point b)
{
	t_point	r;
	int		dx;
	int		dy;
	int		p;
	
	r = a;
	dx = b.x - a.x;
	dy = b.y - a.y;
	p = 2 * dy - dx;
	while (1)
	{
		draw_point(fdf, a, b, r);
		if (r.x == b.x)
			break;
		if (p <= 0)
		{
			p += 2 * dy;
			r.x++;
		}
		else
		{
			p += 2 * (dy - dx);
			r.y++;
			r.x++;
		}
	}
}

void	draw_line(t_fdf *fdf, t_point a, t_point b)
{
	if (a.x > b.x)
		swap_points(&a, &b);
	if (a.x == b.x)
		draw_line_vertical(fdf, a, b);
	else if (a.y == b.y)
		draw_line_horizental(fdf, a, b);
	else if (a.y > b.y)
		fdf_err("Cant Draw");
	else 
		draw_line_positive(fdf, a, b);
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
		for (int i = 0; i < WIN_WIDTH; i += 4) {
			set_pixel(&fdf->img_d, i, j, 0x0);
		}
	}
	for (int j = 10; j < fdf->map.h - 10; j += 4)
	{
		for (int i = 10; i < fdf->map.w - 10; i++) {
			draw_line(fdf, get_point(i, j), get_point(i+1, j-5));
		}
	}
}

void	set_pixel(t_image_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
