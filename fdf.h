/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 12:00:52 by qdegraev          #+#    #+#             */
/*   Updated: 2016/01/05 19:51:54 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAX_WITH 1400
# define MAX_HEIG 1400

# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"

#include <math.h>

typedef struct	s_img
{
	void	*img_ptr;
	char	*img;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_env
{
	int		withd;
	int		hei;
	int		xpos;
	int		ypos;
	int		**map;
	void	*mlx;
	void	*window;
	int		scale;
	int		color;
	t_img	img;
}				t_env;

typedef struct	s_coord
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
}				t_coord;

int		count_nbr(char **split, t_env *e);
int		*str_to_tab(char *line, t_env *e);
int		count_size_tab(char *av);
int		**read_and_stock(char *agv, t_env *e);

#endif
