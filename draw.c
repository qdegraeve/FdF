/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 19:29:18 by qdegraev          #+#    #+#             */
/*   Updated: 2016/01/08 14:02:26 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		draw(t_env *e)
{
	int x;
	int y;
	t_coord c;

	x = 0;
	y = 0;
	while (y < e->hei)
	{
		x = 0;
		while (x < e->withd)
		{
			if (x + 1 < e->withd)
				init_coord_right(&c, e, x, y);
			if (y + 1 < e->hei)
				init_coord_down(&c, e, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int		draw_line_x(t_env *e, t_coord *c, t_octant *i)
{
	int D;
	int y;
	int x;
	int dx;
	int dy;

	dx = i->x;
	dy = i->y;
	D = 2*dy - dx;
	y = 0;
	x = 0;
	put_pixel_img(e, c->x1, c->y1, e->color);
	while (++x < dx)
	{
		D = D + (2 * dy);
		if (D > 0)
		{
			y++;
			D = D - (2 * dx);
		}
		ft_magic(c->octant, x, y, 1, i);
		put_pixel_img(e, i->x + c->x1, i->y + c->y1, e->color);
	}
	return (0);
}

void	put_pixel_img(t_env *e, int x, int y, int color)
{
	int pos;

	pos = (x * e->img.bpp / 8) + (y * e->img.size_line);
	e->img.img[pos] = color % 256;
	e->img.img[pos + 1] = (color >> 8) % 256;
	e->img.img[pos + 2] = (color >> 16) % 256;
}

void	draw_col(t_env *e, t_coord *c)
{
	int x;
	int y;

	x = c->x1;
	y = c->y1;
	while (y++ < c->y2)
		put_pixel_img(e, x, y, e->color);
}

void	mlx_fill_image(t_env *e)
{
	int x;
	int y;

	y = -1;
	while (++y < MAX_WITH)
	{
		x = -1;
		while (++x < MAX_HEIG)
			put_pixel_img(e, x, y, 0x000000);
	}
}
