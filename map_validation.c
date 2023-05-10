/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:58 by segan             #+#    #+#             */
/*   Updated: 2023/05/10 20:59:04 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*map_validation(char *argv)
{
	int		fd;
	t_map	*map;
	char	**file;

	fd = ft_open(argv);
	map = (t_map *)ft_malloc(sizeof(map));
	file = read_map(fd);
	return (map);
}
