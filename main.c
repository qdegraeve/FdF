/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 14:59:55 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/04 16:10:14 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		expose_hook(t_env *e)
{
	draw(e);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos,
			e->ypos);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	ft_putnbr(keycode);
	ft_putendl(" = keycode");
	mlx_clear_window(e->mlx, e->window);
	mlx_fill_image(e);
	if (keycode == 69)
		e->scale = e->scale <= 20 ? e->scale * 1.5 : e->scale;
	if (keycode == 78)
		e->scale = e->scale >= 1.5 ? e->scale / 1.5 : e->scale;
	if (keycode == 124)
		e->angle += 1;
	if (keycode == 123)
		e->angle -= 1;
	if (keycode == 126 && e->ypos > 9)
		e->ypos -= 10;
	if (keycode == 125 && e->ypos < 100)
		e->ypos += 10;
	if (keycode == 27)
		e->deep -= 1;
	if (keycode == 24)
		e->deep += 1;
	draw(e);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos,
			e->ypos);
	if (keycode == 53)
		exit(0);
	return (0);
}

t_env	init_env(char *file)
{
	t_env	e;

	e.map = read_and_stock(file, &e);
	e.scale = 2.0;
	e.deep = 2;
	e.angle = 2;
	e.xpos = 0;
	e.ypos = 0;
	e.color = 100000;
	e.mlx = mlx_init();
	e.window = mlx_new_window(e.mlx, MAX_WITH, MAX_HEIG, file);
	e.img.img_ptr = mlx_new_image(e.mlx, MAX_WITH, MAX_HEIG);
	e.img.img = mlx_get_data_addr(e.img.img_ptr, &e.img.bpp, &e.img.size_line,
			&e.img.endian);
	return (e);
}

int		main(int argc, char **av)
{
	t_env	e;

	if (argc != 2)
		return (0);
	e = init_env(av[1]);
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
	return (0);
}
