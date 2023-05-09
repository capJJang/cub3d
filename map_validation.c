/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:58 by segan             #+#    #+#             */
/*   Updated: 2023/05/09 18:48:00 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_validation(char *argv, char ***map)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	//*map =
}
