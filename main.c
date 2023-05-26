/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:52:42 by segan             #+#    #+#             */
/*   Updated: 2023/05/26 15:26:50 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	*map;

	(void)argc;
	//if (argc != 2)
	//	return (print_error(INVALID_ARG));
	map = map_validation(argv[1]);

}
