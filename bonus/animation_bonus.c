/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 03:44:28 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/14 01:52:22 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	smooth(double x)
{
	return ((sin(PI * x - PI / 2) + 1) / 2);
}

void	anim_scale(void)
{
	t_anim	*anim;
	clock_t	now;
	double	delta_time;

	anim = &get_fdf()->anim;
	if (anim->state)
	{
		now = clock();
		if (anim->last_time == 0)
			anim->last_time = now;
		delta_time = (double)(now - anim->last_time) / CLOCKS_PER_SEC;
		anim->last_time = now;
		anim->progress += delta_time * ANIM_SPEED;
		if (anim->progress >= 1)
		{
			anim->state = 0;
			anim->progress = 1;
			anim->last_time = 0;
		}
	}
}

int	anim_hook(t_fdf *fdf)
{
	if (fdf->anim.state && !fdf->iso)
	{
		anim_scale();
		update(fdf);
	}
	return (0);
}
