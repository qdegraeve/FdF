/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 12:00:52 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/03 18:25:42 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAX_WITH 1400
# define MAX_HEIG 1400
# define DEEPNESS 2

# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"
# include <mlx.h>

# include <math.h>

typedef struct	s_img
{
	void		*img_ptr;
	char		*img;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_octant
{
	int			x;
	int			y;
}				t_octant;

typedef struct	s_coord
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			dx;
	int			dy;
	int			octant;
	t_octant	i;
}				t_coord;

typedef struct	s_calc
{
	int			x;
	int			y;
	int			d;
	int			out;
}				t_calc;

typedef struct	s_env
{
	int			withd;
	int			hei;
	int			xpos;
	int			ypos;
	int			deep;
	int			angle;
	int			**map;
	void		*mlx;
	void		*window;
	float		scale;
	int			color;
	int			ctype;
	t_img		img;
	t_coord		c;
}				t_env;

int				count_nbr(char **split, t_env *e);
int				*str_to_tab(char *line, t_env *e);
int				count_size_tab(char *av);
int				**read_and_stock(char *agv, t_env *e);
int				draw(t_env *e);
int				draw_line_x(t_env *e, t_coord *c, t_octant *i);
void			put_pixel_img(t_env *e, int x, int y, int color);
void			draw_col(t_env *e, t_coord *c);
void			mlx_fill_image(t_env *e);
void			define_octant(t_coord *c);
void			ft_magic(int octant, int x, int y, int out, t_octant *i);
void			init_coord_right(t_coord *c, t_env *e, int x, int y);
void			init_coord_down(t_coord *c, t_env *e, int x, int y);

#endif
