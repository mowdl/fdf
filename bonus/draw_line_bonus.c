/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:13:51 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/13 02:59:43 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

void	draw_line_bresenham(t_fdf *fdf, t_point a, t_point b)
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
		draw_point(fdf, fixe_point(fdf, a),
			fixe_point(fdf, b), fixe_point(fdf, r));
		if (r.x == b.x)
			break ;
		if (p <= 0)
			p += 2 * dy;
		else
		{
			p += 2 * (dy - dx);
			r.y++;
		}
		r.x++;
	}
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
		draw_line_bresenham(fdf, a, b);
	}
}
