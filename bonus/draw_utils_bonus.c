/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:16:24 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/13 03:20:26 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	swap_points(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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

t_point	get_point(t_fdf *fdf, int i, int j)
{
	if (fdf->iso)
		return (iso_transform(&fdf->tr,
				fdf->map.points[i + j * fdf->map.w]));
	return (transform_point(&fdf->tr,
			fdf->map.points[i + j * fdf->map.w]));
}
