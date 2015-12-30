/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afillion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:43:33 by afillion          #+#    #+#             */
/*   Updated: 2015/12/22 14:40:32 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	tmp[n];
	size_t	i;

	i = 0;
	while (i < n)
	{
		tmp[i] = ((char*)src)[i];
		i++;
	}
	i = 0;
	while (i < n && dest)
	{
		((char*)dest)[i] = tmp[i];
		i++;
	}
	((char*)dest)[i] = '\0';
	return (dest);
}
