/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:56:09 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/13 00:39:23 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_point	iso_transform(t_point p)
{
	t_point	pp;

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
	pp.y = p.y * cos(to_rad(-35)) - p.z * sin(to_rad(-35));
	pp.z = p.y * sin(to_rad(-35)) + p.z * cos(to_rad(-35));
	return (pp);
}

t_point	transform_point(t_transform *tr, t_point p)
{
	p.x *= tr->scale.x;
	p.y *= tr->scale.y;
	p.z *= tr->scale.z;
	p = iso_transform(p);
	p.x += tr->pos.x;
	p.y += tr->pos.y;
	p.z += tr->pos.z;
	return (p);
}
