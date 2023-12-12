

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

int main(int ac, char **av)
{
	t_fdf *fdf;

	fdf = get_fdf();
	if (ac != 2)
		fdf_err("Usage: fdf [file_path]\n");
	fdf->map_data.file_path = av[1];
	load_map(fdf);

	fdf_init_mlx(fdf);

	transform(fdf);

	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img_d.img, 0, 0);
	mlx_loop(fdf->mlx);

	fdf_clean();
}
