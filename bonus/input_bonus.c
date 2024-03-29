/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:54:59 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/14 02:25:05 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	scale(t_fdf *fdf, const float s)
{
	if (fdf->iso)
		return ;
	fdf->tr.scale.x *= s;
	fdf->tr.scale.y *= s;
	fdf->tr.scale.z *= s;
}

void	keycode_translation(int keycode, t_fdf *fdf)
{
	const int	pos = 10;

	if (fdf->iso)
		return ;
	if (keycode == KEY_S)
		fdf->tr.pos.y += pos;
	else if (keycode == KEY_W)
		fdf->tr.pos.y -= pos;
	else if (keycode == KEY_A)
		fdf->tr.pos.x -= pos;
	else if (keycode == KEY_D)
		fdf->tr.pos.x += pos;
}

void	keycode_rotation(int keycode, t_fdf *fdf)
{
	const int	rot = 1;

	if (keycode == KEY_UP)
		fdf->tr.rot.x += rot;
	else if (keycode == KEY_DOWN)
		fdf->tr.rot.x -= rot;
	else if (keycode == KEY_RIGHT)
		fdf->tr.rot.z += rot;
	else if (keycode == KEY_LEFT)
		fdf->tr.rot.z -= rot;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		fdf_clean();
		exit(0);
	}
	keycode_translation(keycode, fdf);
	keycode_rotation(keycode, fdf);
	if (keycode == KEY_P)
	{
		fdf->iso = !fdf->iso;
		init_transform(get_fdf());
	}
	if (keycode == KEY_U)
		scale(fdf, 1.2);
	if (keycode == KEY_I)
		scale(fdf, 0.8);
	if (keycode == KEY_Q && fdf->iso != 1)
	{
		fdf->anim.state = 1;
		fdf->anim.progress = 0;
	}
	update(fdf);
	return (0);
}
