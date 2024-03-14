/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:14:56 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/14 00:44:27 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdarg.h>

# include <time.h>

# include <math.h>
# define PI 3.141592654

# define WIN_HEIGHT 800
# define WIN_WIDTH 1200
# define WIN_TITLE "fdf"

# define BG_COLOR 0x111111

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_U 117
# define KEY_I 105
# define KEY_ESC 65307
# define KEY_P 112
# define KEY_Q 113

# define ANIM_SPEED 0.3

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
}		t_vec3;

typedef struct s_vec3_f {
	float	x;
	float	y;
	float	z;
}			t_vec3_f;

typedef struct s_transform {	
	t_vec3_f	scale;
	t_vec3		pos;
	t_vec3		rot;
}				t_transform;

typedef struct s_anim {
	int		state;
	double	progress;
	clock_t	last_time;
}			t_anim;

typedef struct s_fdf {
	t_transform		tr;
	t_image_data	img_d;
	t_map_data		map_data;
	t_map			map;
	t_line			line;
	void			*mlx;
	void			*mlx_win;
	int				iso;
	t_anim			anim;
}					t_fdf;

int		ft_printf(const char *str, ...);

t_fdf	*get_fdf(void);
void	fdf_clean(void);
void	del_with_free(void *content);
int		on_close(void);

void	fdf_err(char *msg);

void	project_to_world(t_fdf *fdf);
void	init_transform(t_fdf *fdf);
t_point	transform_point(t_transform *tr, t_point p);
void	update(t_fdf *fdf);
void	scale(t_fdf *fdf, const float s);
void	parse_points_arr(t_fdf *fdf);

void	draw_map(t_fdf *fdf);
void	draw_point(t_fdf *fdf, t_point a, t_point b, t_point p);
void	draw_line(t_fdf *fdf, t_point a, t_point b);
void	set_pixel(t_image_data *data, int x, int y, int color);

void	swap_points(t_point *a, t_point *b);
void	flip_point(t_point *p);
t_point	fixe_point(t_fdf *fdf, t_point r);
t_point	get_point(t_fdf *fdf, int i, int j);

void	load_map(t_fdf *fdf);

void	normalize_z(t_fdf *fdf);

int		key_hook(int keycode, t_fdf *fdf);

t_point	iso_transform(t_transform *tr, t_point p);

int		anim_hook(t_fdf *fdf);
double	smooth(double x);
#endif
