/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:55 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/13 21:46:26 by mel-meka         ###   ########.fr       */
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

int	lerp(int a, int b, int t)
{
	return (a + (t * (b - a))/ 100);
}

int	lerp_color(int a, int b, int t)
{
	t_vec3	c;

	if (a == b)
		return (a);
	c.x = a >> 16 & 0xFF;
	c.y = a >> 8 & 0xFF;
	c.z = a & 0xFF;

	c.x = lerp(c.x, b >> 16 & 0xFF, t);
	c.y = lerp(c.y, b >> 8 & 0xFF, t);
	c.z = lerp(c.z, b & 0xFF, t);
	return (c.x << 16) | (c.y << 8) | (c.z);
}

int	get_percentage(t_point a, t_point b, t_point p)
{
	t_vec3	d;

	d.x = b.x - a.x;
	d.y = b.y - a.y;
	if (d.x > d.y)
		return ((p.x - a.x) * COLOR_Q / d.x);
	return ((p.y - a.y) * COLOR_Q / d.y);
}

#include <stdio.h>
void	draw_point(t_fdf *fdf, t_point a, t_point b, t_point p)
{
	int	t;

	t = get_percentage(a, b, p);
	set_pixel(&fdf->img_d, p.x, p.y, lerp_color(a.color, b.color, t));
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
