/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:58 by segan             #+#    #+#             */
/*   Updated: 2023/05/22 13:40:43 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_value(char **file)
{
	while (ft_isspace(*file))
		*file++;
}

void	parsing_texture(t_map *map, char **file)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(file[i], "NO ", 3) == 0)
			map->no = store_image(file[i]);
		else if (ft_strncmp(file[i], "SO ", 3) == 0)
			map->no = store_image(file[i]);
		else if (ft_strncmp(file[i], "WE ", 3) == 0)
			map->no = store_image(file[i]);
		else if (ft_strncmp(file[i], "EA ", 3) == 0)
			map->no = store_image(file[i]);
		else if (ft_strncmp(file[i], "F ", 2) == 0)
			map->no = store_image(file[i]);
		else if (ft_strncmp(file[i], "C ", 2) == 0)
		i++;
	}

}

t_map	*map_validation(char *argv)
{
	int		fd;
	t_map	*map;
	char	**file;

	fd = ft_open(argv);
	map = (t_map *)ft_malloc(sizeof(map));
	file = read_map(fd);
	close(fd);
	parsing_texture(map, file);
	parsing_map(map, file);

	return (map);
}
