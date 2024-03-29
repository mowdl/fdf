/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:53:33 by mel-meka          #+#    #+#             */
/*   Updated: 2024/03/11 20:15:51 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

void	del_with_free(void *content)
{
	free(content);
}

void	del_arr(void *arr)
{
	char	**tmp;

	tmp = (char **)arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
}

void	fdf_clean(void)
{
	t_fdf	*fdf;

	fdf = get_fdf();
	if (fdf->map_data.lines)
		ft_lstclear(&fdf->map_data.lines, del_with_free);
	if (fdf->map_data.splited_lines)
		ft_lstclear(&fdf->map_data.splited_lines, del_arr);
	if (fdf->img_d.img)
		mlx_destroy_image(fdf->mlx, fdf->img_d.img);
	if (fdf->mlx)
	{
		if (fdf->mlx_win)
			mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	if (fdf->map.points)
		free(fdf->map.points);
}

int	on_close(void)
{
	fdf_clean();
	exit(0);
	return (0);
}
