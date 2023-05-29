/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:58 by segan             #+#    #+#             */
/*   Updated: 2023/05/29 19:55:28 by segan            ###   ########.fr       */
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

int decimalToHexadecimal(int decimal)
{
	int	ret;

	ret = 0x0;
	while (decimal > 0)
	{
		ret = (ret * 100) + (decimal % 16);
		decimal /= 16;
	}
	return (ret);
}

int	get_texture_floor_ceiling(char *line)
{
	int		ret;
	int		temp;

	ret = 0x0;
	line += 1;
	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		temp = ft_atoi(line);
		//printf("%s\n", line);
		if ((temp < 0 || temp > 255 )|| (temp == 0 && *line != '0'))
			; //에러 출력
		ret = ret * 1000 + temp;
		while (ft_isdigit(*line))
			line++;
		if (*line == ',')
			line++;
		else
			;	//에러 출력
	}
	return (ret);
}

void	validation_texture(t_map *map, char **file)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(file[i], "NO ", 3) == 0)
			map->no = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "SO ", 3) == 0)
			map->so = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "EA ", 3) == 0)
			map->ea = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "WE ", 3) == 0)
			map->we = get_texture_wall(file[i]);
		else if (ft_strncmp(file[i], "F ", 2) == 0)
			map->f = get_texture_floor_ceiling(file[i]);
		else if (ft_strncmp(file[i], "C ", 2) == 0)
			map->c = get_texture_floor_ceiling(file[i]);
		else
			; //에러 출력
		i++;
	}
	//printf("%x\n", map->f);
	//printf("%x\n", map->c);
}

void	start_pos_check(char *line, t_map *map, int *starting_point, int i)
{
	if (ft_strchr(line, 'N'))
	{
		map->y = i - 6;
		map->x = ft_strchr(line, 'N') - line;
		map->facing = 'N';
		(*starting_point)++;
	}
	if (ft_strchr(line, 'S'))
	{
		map->y = i - 6;
		map->x = ft_strchr(line, 'S') - line;
		map->facing = 'S';
		(*starting_point)++;
	}
	if (ft_strchr(line, 'E'))
	{
		map->y = i - 6;
		map->x = ft_strchr(line, 'E') - line;
		map->facing = 'E';
		(*starting_point)++;
	}
	if (ft_strchr(line, 'W'))
	{
		map->y = i - 6;
		map->x = ft_strchr(line, 'W') - line;
		map->facing = 'W';
		(*starting_point)++;
	}
}

int	ele_check(char **file, t_map *map)
{
	size_t	max_width;
	int		i;
	char	 *temp;
	int		starting_point;

	i = 6;
	max_width = 0;
	starting_point = 0;
	while (file[i])
	{
		if (ft_strlen(file[i]) > max_width)
			max_width = ft_strlen(file[i]);
		temp = ft_strtrim(file[i], "SNEW10 ");
		if (*temp != 0)
			// 에러 출력
		free(temp);
		start_pos_check(file[i], map, &starting_point, i);
		i++;
	}
	if (starting_point > 1)
		; //에러 출력
	return (max_width);
}

void	flood_fill(char **map, int i, int j)
{
	if (map[i][j] == '1')
		return ;
	if(map[i][j] == 0)
	{

		printf("error\n"); //에러 출력
		exit(1);
	}
	if (map[i][j] == 'v')
		return ;
	map[i][j] = 'v';
	printf("%d %d\n", i, j);
	flood_fill(map, i - 1, j);
	flood_fill(map, i + 1, j);
	flood_fill(map, i, j + 1);
	flood_fill(map, i, j - 1);
}

void	validation_map(t_map *map, char **file)
{
	int		max_width;
	int		i;
	int		j = 0;
	t_map	test_map;

	i = 6;
	max_width = ele_check(file, map);
	while (file[i++])
		j++;
	map->map = (char **)ft_malloc((j + 1) * sizeof(char *));
	i = 6;
	j = 0;
	while (file[i])
	{
		map->map[j] = (char *)ft_malloc(max_width + 1);
		ft_memset(map->map[j], 0, max_width + 1);
		ft_memcpy(map->map[j], file[i], ft_strlen(file[i]));
		i++;
		j++;
	}
	map->map[j] = (char *)ft_malloc(max_width + 1);
	ft_memset(map->map[j], 0, max_width + 1);
	ft_memcpy(map->map[j], file[i], ft_strlen(file[i]));
	test_map.map = map->map;
	flood_fill(test_map.map, map->y, map->x);
	i = 0;
	while (test_map.map[i])
	{
		j = 0;
		while (test_map.map[i][j])
			flood_fill(test_map.map, i, j++);
		i++;
	}

}

t_map	*map_validation(char *argv)
{
	int		fd;
	t_map	*map;
	char	**file;

	fd = ft_open(argv);
	map = (t_map *)ft_malloc(sizeof(t_map));
	file = read_map(fd);
	validation_texture(map, file);
	validation_map(map, file);
	printf("finished\n");
	return (map);
}
