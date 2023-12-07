/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:14:56 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/06 23:12:51 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdarg.h>

#define HEIGHT 1000
#define WIDTH 1500

typedef struct s_image_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image_data;

typedef struct s_map {
	int	*m;
	int	h;
	int	w;
}		t_map;

typedef struct s_fdf {
	t_image_data	img_d;
	t_map			map;
}					t_fdf;

typedef struct s_vec2 {
	float	x;
	float	y;
}			t_vec2;

typedef struct s_line {
	t_vec2	a;
	t_vec2	b;
}			t_line;

int	ft_printf(const char *str, ...);

void	my_mlx_pixel_put(t_image_data *data, int x, int y, int color);
int		floats_to_color(float f1, float f2, float f3, float f4);
void shade(t_image_data *img_data, int(*f)(int x, int y));

void	draw_line(t_image_data *img_data, t_line line);

void	*load_map(int fd, t_map *map);
