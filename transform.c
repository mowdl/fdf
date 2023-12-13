/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:56:09 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/13 19:55:42 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_init_scale_factor(t_fdf *fdf)
{
	float	hr;
	float	wr;
	float	s;

	s = 1.0;
	hr = (float)fdf->map.h / (float)WIN_HEIGHT;
	wr = (float)fdf->map.w / (float)WIN_WIDTH;

	if (hr > wr)
		return (s / hr);
	else
		return (s / wr);
}

void	project_to_world(t_fdf *fdf)
{
	int	i;
	t_point *p;

	int	factor = get_init_scale_factor(fdf);

	i = 0;
	while (i < fdf->map.h * fdf->map.w)
	{
		p = fdf->map.points + i;
		p->x = (p->x - fdf->map.w / 2) * factor;
		p->y = (p->y - fdf->map.h / 2) * factor;
		i++;
	}
}

double to_rad(const int deg)
{
	return (((double)deg * PI) / 180);
}

t_point	transform_point(t_transform *tr, t_point p)
{
	t_point	pp;
	p.x *= tr->scale.x;
	p.y *= tr->scale.y;
	p.z *= tr->scale.z;

	pp = p;
	pp.x = p.x * cos(to_rad(tr->rot.z)) - p.y * sin(to_rad(tr->rot.z));
	pp.y = p.x * sin(to_rad(tr->rot.z)) + p.y * cos(to_rad(tr->rot.z));
	pp.z = p.z;

	p = pp;
	pp.x = p.x;
	pp.y = p.y * cos(to_rad(tr->rot.x)) - p.z * sin(to_rad(tr->rot.x));
	pp.z = p.y * sin(to_rad(tr->rot.x)) + p.z * cos(to_rad(tr->rot.x));

	pp.x += tr->pos.x;
	pp.y += tr->pos.y;
	pp.z += tr->pos.z;
	return (pp);
}

void	init_transform(t_fdf *fdf)
{
	fdf->tr.scale.x = 0.7;
	fdf->tr.scale.y = 0.7;
	fdf->tr.scale.z = 1;

	fdf->tr.pos.x = WIN_WIDTH / 2;
	fdf->tr.pos.y = WIN_HEIGHT / 2;
	fdf->tr.pos.z = 0;


	fdf->tr.rot.x = 30;
	fdf->tr.rot.y = 0;
	fdf->tr.rot.z = 45;
}
