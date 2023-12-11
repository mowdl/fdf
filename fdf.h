/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:14:56 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/11 16:09:35 by mel-meka         ###   ########.fr       */
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

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	color;
}		t_point;

typedef struct s_map {
	t_point	*points;
	int		h;
	int		w;
}			t_map;

typedef struct s_map_data {
	char	*file_path;
	int		fd;
	t_list	*lines;
	t_list	*splited_lines;
	t_map	map;
}			t_map_data;

typedef struct s_fdf {
	t_image_data	img_d;
	t_map_data		map_data;
	t_map			map;
}					t_fdf;

int	ft_printf(const char *str, ...);

t_fdf	*get_fdf(void);
void	fdf_clean(void);
void	del_with_free(void *content);

void	fdf_err(char *msg);

void	my_mlx_pixel_put(t_image_data *data, int x, int y, int color);
int		floats_to_color(float f1, float f2, float f3, float f4);
void	shade(t_image_data *img_data, int(*f)(int x, int y));

//void	draw_line(t_image_data *img_data, t_line line);

void	load_map(t_fdf *fdf);
