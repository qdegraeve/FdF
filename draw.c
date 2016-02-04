/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 19:29:18 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/04 18:47:28 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		draw(t_env *e)
{
	int		x;
	int		y;
	t_coord	c;

	x = 0;
	y = 0;
	while (y < e->hei)
	{
		x = 0;
		while (x < e->withd)
		{
			init_coord(&c, e, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int		draw_line_x(t_env *e, t_coord *c, t_octant *i)
{
	t_calc	d;
	int		y;
	int		x;

	d.x = i->x;
	d.y = i->y;
	d.d = 2 * d.y - d.x;
	y = 0;
	x = 0;
	put_pixel_img(e, c->x1, c->y1);
	while (++x < d.x)
	{
		d.d = d.d + (2 * d.y);
		if (d.d > 0)
		{
			y++;
			d.d = d.d - (2 * d.x);
		}
		ft_out(c->octant, x, y, i);
		put_pixel_img(e, i->x + c->x1, i->y + c->y1);
	}
	return (0);
}

void	put_pixel_img(t_env *e, int x, int y)
{
	int pos;

	if (x >= MAX_WITH || y >= MAX_HEIG || x < 0 || y < 0)
		return ;
	pos = (x * e->img.bpp / 8) + (y * e->img.size_line);
	e->img.img[pos] = e->color % 256;
	e->img.img[pos + 1] = (e->color >> 8) % 256;
	e->img.img[pos + 2] = (e->color >> 16) % 256;
}

void	draw_col(t_env *e, t_coord *c)
{
	int x;
	int y;

	x = c->x1;
	y = c->y1;
	while (y++ < c->y2)
		put_pixel_img(e, x, y);
}

void	mlx_fill_image(t_env *e)
{
	int x;
	int y;

	y = -1;
	e->color = 0x000000;
	while (++y < MAX_WITH)
	{
		x = -1;
		while (++x < MAX_HEIG)
			put_pixel_img(e, x, y);
	}
}
