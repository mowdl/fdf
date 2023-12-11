

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

int main(int ac, char **av)
{
	t_fdf *fdf;

	fdf = get_fdf();
	if (ac != 2)
		fdf_err("Usage: fdf [file_path]\n");
	fdf->map_data.file_path = av[1];
	load_map(fdf);

	int i = 0;

	while (i < fdf->map.w * fdf->map.h)
	{
		t_point p = fdf->map.points[i];
		ft_printf("x: %d, y: %d, z: %d, color: %X\n", p.x, p.y, p.z, p.color);
		i++;
	}

	fdf_clean();
}
