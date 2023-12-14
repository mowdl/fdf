

#include "mlx.h"
#include "fdf.h"

#include <stdlib.h>
#include <math.h>
#include <fcntl.h>

t_fdf	*get_fdf()
{
	static t_fdf fdf;
	return (&fdf);
}

void	fdf_init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		fdf_err("Error with mlx\n");
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (fdf->mlx_win == NULL)
		fdf_err("Error with mlx\n");
	fdf->img_d.img = mlx_new_image(fdf->mlx, 1920, 1080);
	if (fdf->img_d.img == NULL)
		fdf_err("Error with mlx\n");
	fdf->img_d.addr = mlx_get_data_addr(fdf->img_d.img, &fdf->img_d.bits_per_pixel, &fdf->img_d.line_length,
								&fdf->img_d.endian);
}

#include<stdio.h>

int	key_hook(int keycode, t_fdf *fdf)
{
	float	s;
	int		rot;

	rot = 1;
	if (keycode == 53)
	{
		fdf_clean();
		exit(0);
	}
	else if (keycode == KEY_W)
	{
		s = 1.2;
		fdf->tr.scale.x *= s;
		fdf->tr.scale.y *= s;
		fdf->tr.scale.z *= s;
		update(fdf);
	}
	else if (keycode == KEY_S)
	{
		s = 0.8;
		fdf->tr.scale.x *= s;
		fdf->tr.scale.y *= s;
		fdf->tr.scale.z *= s;
		update(fdf);
	}
	else if (keycode == KEY_UP)
	{
		fdf->tr.rot.x += rot;
		update(fdf);
	}
	else if (keycode == KEY_DOWN)
	{
		fdf->tr.rot.x -= rot;
		update(fdf);
	}
	else if (keycode == KEY_RIGHT)
	{
		fdf->tr.rot.z += rot;
		update(fdf);
	}
	else if (keycode == KEY_LEFT)
	{
		fdf->tr.rot.z -= rot;
		update(fdf);
	}
	return (0);
}

void	update(t_fdf *fdf)
{
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img_d.img, 0, 0);
}

int main(int ac, char **av)
{
	t_fdf *fdf;

	fdf = get_fdf();
	if (ac != 2)
		fdf_err("Usage: fdf [file_path]\n");
	fdf->map_data.file_path = av[1];
	load_map(fdf);

	fdf_init_mlx(fdf);

	project_to_world(fdf);
	init_transform(fdf);

	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img_d.img, 0, 0);
	mlx_key_hook(fdf->mlx_win, key_hook, fdf);
	mlx_loop(fdf->mlx);

	fdf_clean();
}
