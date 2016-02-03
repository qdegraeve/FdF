/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 11:58:01 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/03 14:59:18 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		count_nbr(char **split, t_env *e)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	if (!e->withd || e->withd < i)
		e->withd = i;
	return (i);
}

int		*str_to_tab(char *line, t_env *e)
{
	int		i;
	char	**tmp;
	int		*tab;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	tab = (int*)malloc(count_nbr(tmp, e) * sizeof(tab));
	while (tmp[i])
	{
		tab[i] = ft_getnbr(tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (tab);
}

int		count_size_tab(char *av)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int		**read_and_stock(char *agv, t_env *e)
{
	int		fd;
	int		i;
	int		**tab;
	char	*line;

	i = 0;
	tab = (int**)malloc(sizeof(*tab) * (count_size_tab(agv) + 1));
	fd = open(agv, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tab[i++] = str_to_tab(line, e);
		free(line);
	}
	tab[i] = NULL;
	e->hei = i;
	close(fd);
	return (tab);
}
