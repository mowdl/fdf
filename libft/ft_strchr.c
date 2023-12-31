/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-meka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:07:23 by mel-meka          #+#    #+#             */
/*   Updated: 2023/11/11 17:12:42 by mel-meka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*r;
	char	ch;

	ch = (char)c;
	r = (char *)s;
	while (*r != ch)
	{
		if (*r == '\0')
			return (0);
		r++;
	}
	return (r);
}
