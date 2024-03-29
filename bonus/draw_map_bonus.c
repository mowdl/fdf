/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:10:55 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/13 02:58:46 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_background(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			set_pixel(&fdf->img_d, i, j, BG_COLOR);
			i++;
		}
		j++;
	}
}

void	draw_map(t_fdf *fdf)
{
	int	i;
	int	j;

	draw_background(fdf);
	j = 0;
	while (j < fdf->map.h)
	{
		i = 0;
		while (i < fdf->map.w)
		{
			if (i > 0)
				draw_line(fdf, get_point(fdf, i - 1, j), get_point(fdf, i, j));
			if (j > 0)
				draw_line(fdf, get_point(fdf, i, j - 1), get_point(fdf, i, j));
			i++;
		}
		j++;
	}
}

void	set_pixel(t_image_data *data, int x, int y, int color)
{
	char			*dst;
	unsigned int	c;

	if (x < 0 || y < 0)
		return ;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	c = mlx_get_color_value(get_fdf()->mlx, color);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	ft_memcpy(dst, &c, data->bits_per_pixel / 8);
}
