/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:56:09 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/12 14:12:43 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_point *point, int factor)
{
	point->x *= factor;
	point->y *= factor;
	point->z *= factor;
}

int	get_init_scale_factor(t_fdf *fdf)
{
	float	hr;
	float	wr;
	float	s;

	s = 0.8f;
	hr = (float)fdf->map.h / (float)WIN_HEIGHT;
	wr = (float)fdf->map.w / (float)WIN_WIDTH;

	if (hr > wr)
		return (s / hr);
	else
		return (s / wr);
}


#include<stdio.h>

void	transform(t_fdf *fdf)
{
	int	i;

	int	factor = get_init_scale_factor(fdf);
	printf("factor: %d\n", factor);

	i = 0;
	while (i < fdf->map.h * fdf->map.w)
	{
		scale(fdf->map.points + i, factor);
		i++;
	}
}
