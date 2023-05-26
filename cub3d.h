/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:49:29 by segan             #+#    #+#             */
/*   Updated: 2023/05/26 16:28:49 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <mlx.h>

# define INVALID_ARG 1
# define INVALID_FILE 2


typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	f[8];
	char	s[8];
}				t_map;


//util func start
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_isspace(int c);
void	*ft_malloc(long size);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int o);
char	*ft_strrchr(const char *s, int o);
//util end

//error funcs start
int		print_error(int err);
char	*get_err(int err);
//error funcs end


char	*ft_strjoin2(char *s1, char *s2, int s1_free, int s2_free);
int		ft_open(const char *file);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char const *s, char c);


t_map	*map_validation(char *argv);
char	**read_map(int fd);
char	*get_next_line(int fd);

#endif
