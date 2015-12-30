/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 17:42:49 by qdegraev          #+#    #+#             */
/*   Updated: 2015/12/02 18:50:22 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa(int n)
{
	char	*itoa;
	int		len;
	int		tmp;
	int		sign;

	tmp = n;
	len = 2 + (n < 0);
	sign = (n < 0) ? -1 : 1;
	while ((tmp = tmp / 10))
		len++;
	itoa = ft_strnew(len--);
	itoa[len--] = '\0';
	itoa[len--] = sign * (n % 10) + '0';
	while ((n = n / 10))
		itoa[len--] = sign * (n % 10) + '0';
	if (sign < 0)
		itoa[len] = '-';
	return (itoa);
}
