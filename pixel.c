/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:37 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/04 16:13:00 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "fdf.h"

void	define_octant(t_coord *c)
{
	c->dy = c->y2 - c->y1;
	c->dx = c->x2 - c->x1;
	if (c->dx == 0)
	{
		c->octant = 8;
		return ;
	}
	if (c->dx >= 0 && c->dy >= 0 && c->dx >= c->dy)
		c->octant = 0;
	if (c->dy >= 0 && c->dx >= 0 && c->dx <= c->dy)
		c->octant = 1;
	if (c->dx <= 0 && c->dy >= 0 && c->dy >= ft_abs(c->dx))
		c->octant = 2;
	if (c->dx <= 0 && c->dy >= 0 && ft_abs(c->dx) >= c->dy)
		c->octant = 3;
	if (c->dx <= 0 && c->dy <= 0 && ft_abs(c->dx) >= ft_abs(c->dy))
		c->octant = 4;
	if (c->dx <= 0 && c->dy <= 0 && ft_abs(c->dx) <= ft_abs(c->dy))
		c->octant = 5;
	if (c->dx >= 0 && c->dy <= 0 && c->dx <= ft_abs(c->dy))
		c->octant = 6;
	if (c->dx >= 0 && c->dy <= 0 && c->dx >= ft_abs(c->dy))
		c->octant = 7;
}

void	ft_in(int octant, int x, int y, t_octant *i)
{
	i->x = x;
	i->y = y;
	if (octant == 3 || octant == 4)
		i->x = -x;
	if (octant == 7 || octant == 4)
		i->y = -y;
	if (octant == 1 || octant == 2 || octant == 5 || octant == 6)
	{
		i->x = (octant < 3) ? y : -y;
		i->y = (octant > 1 && octant < 6) ? -x : x;
	}
}

void	ft_out(int octant, int x, int y, t_octant *i)
{
	int		out;

	out = 1;
	i->x = x;
	i->y = y;
	if (out == 1 && octant == 6)
	{
		octant = 2;
		out = 2;
	}
	if (out == 1 && octant == 2)
		octant = 6;
	if (octant == 3 || octant == 4)
		i->x = -x;
	if (octant == 7 || octant == 4)
		i->y = -y;
	if (octant == 1 || octant == 2 || octant == 5 || octant == 6)
	{
		i->x = (octant < 3) ? y : -y;
		i->y = (octant > 1 && octant < 6) ? -x : x;
	}
}

void	init_coord(t_coord *c, t_env *e, int x, int y)
{
	t_octant	i;

	e->color = 0x0000FF;
	c->x1 = e->scale * (x) + ((e->hei - y) * e->angle);
	c->y1 = e->scale * (y) - (e->map[y][x] * e->deep);
	if (x + 1 < e->withd)
	{
		c->x2 = e->scale * (x + 1) + ((e->hei - y) * e->angle);
		c->y2 = e->scale * (y) - (e->map[y][x + 1] * e->deep);
		define_octant(c);
		ft_in(c->octant, c->dx, c->dy, &i);
		c->octant == 8 ? draw_col(e, c) : draw_line_x(e, c, &i);
	}
	if (y + 1 < e->hei)
	{
		c->x2 = e->scale * (x) + ((e->hei - (y + 1)) * e->angle);
		c->y2 = e->scale * ((y + 1)) - (e->map[y + 1][x] * e->deep);
		define_octant(c);
		ft_in(c->octant, c->dx, c->dy, &i);
		c->octant == 8 ? draw_col(e, c) : draw_line_x(e, c, &i);
	}
}
