/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 12:00:52 by qdegraev          #+#    #+#             */
/*   Updated: 2015/12/30 18:16:27 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"

int		count_nbr(char **split);
int		*str_to_tab(char *line);
int		count_size_tab(char *av);
int		**read_and_stock(char *agv);

#endif
