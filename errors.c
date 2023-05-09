/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:15:39 by segan             #+#    #+#             */
/*   Updated: 2023/05/09 18:41:44 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*get_err(int err)
{
	if (err == INVALID_ARG)
		return ("Invalid arg\n");
	else if (err == INVALID_MAP)
		return ("Invalid map\n");
	return (NULL);
}

int	print_error(int err)
{
	ft_putendl_fd(get_err(err), 2);
	return (1);
}
