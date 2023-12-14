/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:07:16 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/14 21:11:06 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	lerp(int a, int b, float t)
{
	return (a + t * (float)(b - a));
}

int	lerp_color(int a, int b, float t)
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
	return ((c.x << 16) | (c.y << 8) | (c.z));
}

int	fdf_abs(int a)
{
	if (a > 0)
		return (a);
	return (-a);
}

float	get_percentage(t_point a, t_point b, t_point p)
{
	t_vec3	d;

	d.x = b.x - a.x;
	d.y = b.y - a.y;
	if (fdf_abs(d.x) > fdf_abs(d.y))
		return ((float)(p.x - a.x) / (float)d.x);
	return ((float)(p.y - a.y) / (float)d.y);
}

void	draw_point(t_fdf *fdf, t_point a, t_point b, t_point p)
{
	float	t;

	if (p.x < 0 || p.y < 0 || p.y > WIN_HEIGHT || p.x > WIN_WIDTH)
		return ;
	t = get_percentage(a, b, p);
	set_pixel(&fdf->img_d, p.x, p.y, lerp_color(a.color, b.color, t));
}
