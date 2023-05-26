/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:58 by segan             #+#    #+#             */
/*   Updated: 2023/05/26 16:35:41 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_wall(char *line)
{
	line += 2;
	while (ft_isspace(*line))
		line++;
	return (ft_strdup(line));
}


int	get_texture_floor_ceiling(char *line)
{
	int		ret;
	int		i;
	int		temp;

	i = 0;
	ret = 0;
	line += 1;
	while (ft_isspace(*line))
		line++;
	if(ft_strchr(line, '.') == ft_strrchr(line, ','))
		;	//에러 출력
	while (i < 3)
	{
		temp = ft_atoi(line);
		if (temp < 0 && temp > 256)
			; //에러 출력
		ret = ret * 10 +
		while (ft_isdigit(line))
			line++;
		mlx_pixel_put

	}

	return ();
}

void	validation_texture(t_map *map, char **file)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(file[i], "NO", 3) == 0)
			map->no = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "SO ", 3) == 0)
			map->so = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "EA ", 3) == 0)
			map->ea = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "WE ", 3) == 0)
			map->we = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "F ", 2) == 0)
			map->f = get_texture_floor_ceiling(file[i], 2);
		else if (ft_strncmp(file[i], "C ", 2) == 0)
			map->c = get_texture_floor_ceiling(file[i], 2);
		else
			; //에러 출력
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
	validation_texture(map, file);
	validation_map(map, file);
	return (map);
}
