/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:13:01 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/06 21:48:46 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_image_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	floats_to_color(float f1, float f2, float f3, float f4)
{
	unsigned char	uc1;
	unsigned char	uc2;
	unsigned char	uc3;
	unsigned char	uc4;
	int				result;

    uc1 = (unsigned char)(f4 * 255.0f);
    uc2 = (unsigned char)(f3 * 255.0f);
    uc3 = (unsigned char)(f2 * 255.0f);
    uc4 = (unsigned char)(f1 * 255.0f);
    result = 0;
    result |= uc1;
    result |= uc2 << 8;
    result |= uc3 << 16;
    result |= uc4 << 24;
    return (result);
}

void shade(t_image_data *img_data, int(*f)(int x, int y))
{
	int	i;
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			my_mlx_pixel_put(img_data, i, j, f(i, j));
			i++;
		}
		j++;
	}
}
