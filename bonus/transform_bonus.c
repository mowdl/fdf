/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:56:09 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/14 01:06:58 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	normalize_z(t_fdf *fdf)
{
	t_map *const	map = &fdf->map;
	const int		size = map->w * map->h;
	int				i;
	int				max;
	float			scale;

	max = 0;
	i = 0;
	while (i < size)
	{
		if (map->points[i].z > max)
			max = map->points[i].z;
		i++;
	}
	if (max == 0)
		max = 1;
	scale = (float)WIN_HEIGHT / (float)(max * 2);
	fdf->tr.scale.z *= scale;
}

void	project_to_world(t_fdf *fdf)
{
	int		i;
	t_point	*p;
	int		factor;
	float	hr;
	float	wr;

	hr = (float)fdf->map.h / (float)WIN_HEIGHT;
	wr = (float)fdf->map.w / (float)WIN_WIDTH;
	if (hr > wr)
		factor = (1 / hr);
	else
		factor = (1 / wr);
	i = 0;
	while (i < fdf->map.h * fdf->map.w)
	{
		p = fdf->map.points + i;
		p->x = (p->x - fdf->map.w / 2) * factor;
		p->y = (p->y - fdf->map.h / 2) * factor;
		i++;
	}
}

double	to_rad(const int deg)
{
	return (((double)(deg % 360) *PI) / 180);
}

t_point	transform_point(t_transform *tr, t_point p)
{
	t_point	pp;

	p.x *= tr->scale.x;
	p.y *= tr->scale.y;
	p.z *= tr->scale.z * smooth(get_fdf()->anim.progress);
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

t_point	iso_transform(t_transform *tr, t_point p)
{
	t_point	pp;

	p.x *= tr->scale.x;
	p.y *= tr->scale.y;
	p.z *= tr->scale.z;
	pp = p;
	pp.x = p.x;
	pp.y = p.y * cos(to_rad(90)) - p.z * sin(to_rad(90));
	pp.z = p.y * sin(to_rad(90)) + p.z * cos(to_rad(90));
	p = pp;
	pp.x = p.z * sin(to_rad(-45)) + p.x * cos(to_rad(-45));
	pp.y = p.y;
	pp.z = p.z * cos(to_rad(-45)) - p.x * sin(to_rad(-45));
	p = pp;
	pp.x = p.x;
	pp.y = p.y * cos(to_rad(-35.264)) - p.z * sin(to_rad(-35.264));
	pp.z = p.y * sin(to_rad(-35.264)) + p.z * cos(to_rad(-35.264));
	pp.x += tr->pos.x;
	pp.y += tr->pos.y;
	pp.z += tr->pos.z;
	return (pp);
}

void	init_transform(t_fdf *fdf)
{
	const float	s = 0.6;

	fdf->anim.progress = 1;
	fdf->anim.state = 0;
	fdf->tr.scale.x = 1 * s;
	fdf->tr.scale.y = 1 * s;
	fdf->tr.scale.z = 0.8 * s;
	normalize_z(fdf);
	fdf->tr.pos.x = WIN_WIDTH / 2;
	fdf->tr.pos.y = WIN_HEIGHT / 2;
	fdf->tr.pos.z = 0;
	fdf->tr.rot.x = 45;
	fdf->tr.rot.y = 0;
	fdf->tr.rot.z = 45;
}
