

#include "mlx.h"
#include "fdf.h"

#include <stdlib.h>
#include <math.h>
#include <fcntl.h>

int	print_err(int r)
{
	if (r == 1)
		ft_printf("usage: fdf [file_name]\n");
	else if (r == 2)
		ft_printf("Could not read file\n");
	return 1;
}

void print_map(t_map *map)
{
	int i = 0;
	int j = 0;
	while (j < map->h)
	{
		i = 0;
		while (i < map->w)
		{
			ft_printf("%d\t", map->m[i + j*map->w]);
			i++;
		}
		ft_printf("\n");
		j++;
	}
}

int main(int ac, char **av)
{
	int	fd;
	t_fdf fdf;

	if (ac != 2)
		return (print_err(1));
	fd = open(av[1], O_RDWR);
	if (fd < 0)
		return (print_err(2));
	load_map(fd, &fdf.map);
	print_map(&fdf.map);
}
