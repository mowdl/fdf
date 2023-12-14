/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:53:33 by mel-meka          #+#    #+#             */
/*   Updated: 2023/12/14 20:59:39 by mel-meka         ###   ########.fr       */
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
	if (fdf->map_data.lines != 0)
		ft_lstclear(&fdf->map_data.lines, del_with_free);
	if (fdf->map_data.splited_lines != 0)
		ft_lstclear(&fdf->map_data.lines, del_arr);
}
