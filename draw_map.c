/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:55 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/13 19:55:42 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	fixe_point(t_fdf *fdf, t_point r);

void	swap_points(t_point *a, t_point *b)
{
	t_point tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


#include <stdio.h>
void	draw_point(t_fdf *fdf, t_point a, t_point b, t_point p)
{
	int	color;
	int	t;

	t = ((p.x - a.x) * 100) / (b.x - a.x);
	color = a.color + (t * (b.color - a.color)) / 100;

	set_pixel(&fdf->img_d, p.x, p.y, color);
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
	int		sign;

	if (a.x > b.x)
		sign = -1;
	else
		sign = 1;
	p = a;
	while (p.x != b.x)
	{
		draw_point(fdf, a, b, p);
		p.x += sign;
	}
}

void	draw_line_Bresenham(t_fdf *fdf, t_point a, t_point b)
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
		draw_point(fdf, a, b, fixe_point(fdf, r));

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

void	flip_point(t_point *p)
{
	int	tmp;
	tmp = p->x;
	p->x = p->y;
	p->y = tmp;
}

t_point	fixe_point(t_fdf *fdf, t_point r)
{
	t_point	c;

	c = r;
	if (fdf->line.flipped)
	{
		flip_point(&c);
	}
	if (fdf->line.negative)
		c.y *= -1;
	return (c);
}

void	draw_line(t_fdf *fdf, t_point a, t_point b)
{
	if (a.x == b.x)
		draw_line_vertical(fdf, a, b);
	else if (a.y == b.y)
		draw_line_horizental(fdf, a, b);
	else
	{
		fdf->line.negative = 0;
		fdf->line.flipped = 0;
		if (a.x > b.x)
			swap_points(&a, &b);
		if (a.y > b.y)
		{
			a.y *= -1;
			b.y *= -1;
			fdf->line.negative = 1;
		}
		if ((b.y - a.y) > (b.x - a.x))
		{
			flip_point(&a);
			flip_point(&b);
			fdf->line.flipped = 1;
		}	
		draw_line_Bresenham(fdf, a, b);
	}
}

t_point	get_point(t_fdf *fdf, int i, int j)
{
	return (transform_point(&fdf->tr, fdf->map.points[i + j * fdf->map.w]));
}

void	draw_background(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			set_pixel(&fdf->img_d, i, j, 0x0E1116);
			i++;
		}
		j++;
	}
}

void	draw_map(t_fdf *fdf)
{
	int	i;
	int	j;

	draw_background(fdf);
	j = 0;
	while (j < fdf->map.h)
	{
		i = 0;
		while (i < fdf->map.w)
		{
			if (i > 0)
			draw_line(fdf, get_point(fdf, i-1, j), get_point(fdf, i, j));
			if (j > 0)
			draw_line(fdf, get_point(fdf, i, j-1), get_point(fdf, i, j));
			i++;
		}
		j++;
	}
	j++;
}

void	set_pixel(t_image_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
