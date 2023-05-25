/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:37:37 by segan             #+#    #+#             */
/*   Updated: 2023/05/11 15:48:23 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_open(const char *file)
{
	int	fd;

	if (ft_strnstr(file, ".cub", ft_strlen(file)) == NULL)
	{
		print_error(INVALID_FILE);
		exit(1);
	}
	fd = open(file, O_RDONLY);
	if (fd < -1)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	return (fd);
}

char	*ft_strjoin2(char *s1, char *s2, int s1_free, int s2_free)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;
	size_t	ptr_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr_len = s1_len + s2_len;
	ptr = (char *)malloc(ptr_len + 1);
	if (ptr == (void *)0)
		return ((void *)0);
	ft_bzero(ptr, s1_len + s2_len);
	while (s1_len--)
		*ptr++ = *s1++;
	while (s2_len--)
		*ptr++ = *s2++;
	*ptr = 0;
	if (s1_free)
		free(s1);
	if (s2_free)
		free(s2);
	return (ptr - ptr_len);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == 'v' || c == 'r' || c == 'f')
		return (1);
	return (0);
}

void	*ft_malloc(long size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	return (ret);
}
