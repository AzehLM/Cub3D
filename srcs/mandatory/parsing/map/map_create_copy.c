/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:47:16 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:47:17 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map_processing.h"
#include "map_types.h"
#include "map_validation.h"
#include "parsing.h"

static void	init_tmp(t_filling *tmp, t_infos *infos, t_ext_map *ext_map)
{
	tmp->i = 0;
	tmp->j = 0;
	if (infos->data->lines[ext_map->map_start + tmp->i])
	{
		tmp->src_len = \
			ft_strlen(infos->data->lines[ext_map->map_start + tmp->i]);
		if (tmp->src_len > 0)
			tmp->c = infos->data->lines[ext_map->map_start + tmp->i][tmp->j];
		else
			tmp->c = ' ';
	}
	else
	{
		tmp->src_len = 0;
		tmp->c = ' ';
	}
}

static void	update_len(t_ext_map *ext_map, t_infos *infos, t_filling *tmp)
{
	if (infos->data->lines[ext_map->map_start + tmp->i])
		tmp->src_len = \
			ft_strlen(infos->data->lines[ext_map->map_start + tmp->i]);
	else
		tmp->src_len = 0;
	ext_map->map[tmp->i + 1][0] = ' ';
	tmp->j = 0;
}

static void	fill_extended_map(t_ext_map *ext_map, t_infos *infos)
{
	t_filling	tmp;

	init_tmp(&tmp, infos, ext_map);
	while (tmp.i < ext_map->height)
	{
		update_len(ext_map, infos, &tmp);
		while (tmp.j < tmp.src_len)
		{
			tmp.c = infos->data->lines[ext_map->map_start + tmp.i][tmp.j];
			if (is_valid_map_char(tmp.c) == true)
				ext_map->map[tmp.i + 1][tmp.j++ + 1] = tmp.c;
			else
				ext_map->map[tmp.i + 1][tmp.j++ + 1] = ' ';
		}
		tmp.j = tmp.src_len;
		while (tmp.j < ext_map->width + 1)
		{
			ext_map->map[tmp.i + 1][tmp.j + 1] = ' ';
			tmp.j++;
		}
		ext_map->map[tmp.i + 1][ext_map->width + 2] = '\0';
		tmp.i++;
	}
}

char	**create_extended_map(t_infos *infos, t_ext_map *ext_map)
{
	ext_map->map = init_extended_map(ext_map);
	if (ext_map->map == NULL)
		return (NULL);
	if (init_map_borders(ext_map->map, ext_map) == false)
		return (NULL);
	fill_extended_map(ext_map, infos);
	return (ext_map->map);
}

void	mark_spaces_as_exterior(t_map_data map_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_data.height)
	{
		j = 0;
		while (j < map_data.width)
		{
			if (map_data.map[i][j] == ' ')
				map_data.map[i][j] = 'X';
			j++;
		}
		i++;
	}
}
