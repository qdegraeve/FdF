/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afillion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 17:12:04 by afillion          #+#    #+#             */
/*   Updated: 2015/12/28 10:39:03 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*str;

	if (src == NULL)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(src))))
		return (NULL);
	ft_strcpy(str, src);
	return (str);
}
