/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:15:39 by segan             #+#    #+#             */
/*   Updated: 2023/05/10 21:08:01 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_err(int err)
{
	if (err == INVALID_ARG)
		return ("Invalid argc");
	else if (err == INVALID_FILE)
		return ("Invalid file");
	return (NULL);
}

int	print_error(int err)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(get_err(err), 2);
	return (1);
}
