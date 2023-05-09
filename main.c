/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:52:42 by segan             #+#    #+#             */
/*   Updated: 2023/05/09 18:49:03 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	char	**map;

	if (argc != 2)
		return (print_error(INVALID_ARG));
	if (map_validation(argv[1], &map))
		return (print_error(INVALID_MAP));
}
