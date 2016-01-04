/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:37 by qdegraev          #+#    #+#             */
/*   Updated: 2016/01/04 19:13:37 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "fdf.h"

/*int		distance()
{
	int 
}*/

void	put_pixel_img(t_env *e, int x, int y, int color)
{
	int pos;

	pos = (x * e->img.bpp / 8) + (y * e->img.size_line);
	e->img.img[pos] = color % 256;
	e->img.img[pos + 1] = (color >> 8) % 256;
	e->img.img[pos + 2] = (color >> 16) % 256;
	//img->img[pos + 3] = (color >> 24) % 256;
}

void	mlx_fill_image(t_env *e)
{
	int x;
	int y;

	y = -1;
	while (++y < e->hei * e->scale)
	{
		x = -1;
		while (++x < e->withd * e->scale)
		{
			put_pixel_img(e, x, y, 0x000000);
		}
	}
}

int		draw_line(t_env *e, int x, int y)
{
	int j;

	j = 1;
	while (j < e->scale)
	{
		put_pixel_img(e, x + j, y, e->color);
		j++;
	}
	return (0);
}

int		draw_col(t_env *e, int x, int y)
{
	int i;

	i = 1;
	while (i < e->scale)
	{
		put_pixel_img(e, x, i + y, e->color);
		i++;
	}
	return (0);
}

int		draw(t_env *e)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < e->hei)
	{
		x = 0;
		while (x < e->withd)
		{
			e->color = (e->map[y][x] == 10) ? 0xFFFFFF : 0x00FF00;
			put_pixel_img(e, (x * e->scale), (y * e->scale), e->color);
			if (x + 1 < e->withd)
			{
				e->color = (e->map[y][x] == e->map[y][x + 1]) ? 0xFF0000 : 0x0000FF;
				draw_line(e, (x * e->scale), (y * e->scale));
			}
			if (y + 1 < e->hei)
			{
				e->color = (e->map[y][x] == e->map[y + 1][x]) ? 0xFF0000 : 0x0000FF;
				draw_col(e, (x * e->scale), (y * e->scale));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int		expose_hook(t_env *e)
{
	draw(e);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	ft_putnbr(keycode);
	ft_putendl(" = keycode");
	if (keycode == 69 || keycode == 24)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->scale *= 2;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 78 || keycode == 27)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->scale /= 2;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 123)
	{
		e->xpos -= 10;
		mlx_clear_window(e->mlx, e->window);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 124)
	{
		e->xpos += 10;
		mlx_clear_window(e->mlx, e->window);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 53)
		exit(0);
	return (0);
}

void	init_env(t_env *e, char *file)
{
	e->map = read_and_stock(file, e);
	e->scale = 1;
	e->xpos = 0;
	e->ypos = 0;
	e->mlx = mlx_init();
	e->window = mlx_new_window(e->mlx, 1600, 1600, "prout");
	e->img.img_ptr = mlx_new_image(e->mlx, 600 , 600);
	e->img.img = mlx_get_data_addr(e->img.img_ptr, &e->img.bpp, &e->img.size_line, &e->img.endian);
}

int		main(int argc, char **av)
{
	t_env	e;
	int		x;
	int		y;
	int		**map;

	init_env(&e, av[1]);
	mlx_key_hook(e.window, key_hook, &e);
	mlx_expose_hook(e.window, expose_hook, &e);
	ft_putendl(e.img.img);
	ft_putnbr(e.img.bpp);
	ft_putendl(" = bpp");
	ft_putnbr(e.img.size_line);
	ft_putendl(" = size_line");
	ft_putnbr(e.img.endian);
	ft_putendl(" = endian");
	ft_putnbr(e.withd);
	ft_putendl(" = e.withd");
	ft_putnbr(e.hei);
	ft_putendl(" = e.hei");
	ft_putnbr(e.scale);
	ft_putendl(" = e.scale");
	mlx_loop(e.mlx);
	return(0);
}
