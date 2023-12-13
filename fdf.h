/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:14:56 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/13 21:52:57 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdarg.h>

#include <math.h>
#define PI 3.141592654

#define WIN_HEIGHT 1000
#define WIN_WIDTH 1500
#define WIN_TITLE "fdf"

# define KEY_W 13
# define KEY_S 1
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define COLOR_Q 10

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

typedef struct s_line {
	int	negative;
	int	flipped;
}		t_line;

typedef struct s_vec3 {
	int	x;
	int	y;
	int	z;
} t_vec3;

typedef struct s_vec3_f {
	float	x;
	float	y;
	float	z;
}			t_vec3_f;

typedef struct s_transform {	
	t_vec3_f	scale;
	t_vec3		pos;
	t_vec3		rot;
}		t_transform;

typedef struct s_fdf {
	t_transform		tr;
	t_image_data	img_d;
	t_map_data		map_data;
	t_map			map;
	t_line			line;
	void			*mlx;
	void			*mlx_win;
}					t_fdf;

int	ft_printf(const char *str, ...);

t_fdf	*get_fdf(void);
void	fdf_clean(void);
void	del_with_free(void *content);

void	fdf_err(char *msg);

void	draw_map(t_fdf *fdf);
void	set_pixel(t_image_data *data, int x, int y, int color);
void	project_to_world(t_fdf *fdf);
void	init_transform(t_fdf *fdf);
t_point	transform_point(t_transform *tr, t_point p);
void	update(t_fdf *fdf);


void	load_map(t_fdf *fdf);
