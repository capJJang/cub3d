/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:49:29 by segan             #+#    #+#             */
/*   Updated: 2023/05/09 18:49:10 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# define INVALID_ARG 1
# define INVALID_MAP 2

//libft func start
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
//libft func end

//error funcs start
int			print_error(int err);
const char	*get_err(int err);
//error funcs end

int			map_validation(char *argv, char ***map);
#endif
