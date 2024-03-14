/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_transform_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:53:54 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/14 01:56:10 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static double	to_rad(const int deg)
{
	return (((double)(deg % 360) *PI) / 180);
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
	pp.y = p.y * cos(to_rad(-35)) - p.z * sin(to_rad(-35));
	pp.z = p.y * sin(to_rad(-35)) + p.z * cos(to_rad(-35));
	pp.x += tr->pos.x;
	pp.y += tr->pos.y;
	pp.z += tr->pos.z;
	return (pp);
}
