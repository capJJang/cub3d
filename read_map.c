/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:05:35 by segan             #+#    #+#             */
/*   Updated: 2023/05/10 20:55:02 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_map(int fd)
{
	char	*map;
	char	*temp;

	map = NULL;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		if (*temp == '\n')
		{
			free(temp);
			continue ;
		}
		map = ft_strjoin2(map, temp, 1, 1);
	}
	return (ft_split(map, '\n'));
}
