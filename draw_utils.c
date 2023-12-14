/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:16:24 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/14 21:33:41 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (transform_point(&fdf->tr,
			fdf->map.points[i + j * fdf->map.w]));
}
