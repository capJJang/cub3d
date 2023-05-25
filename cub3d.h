#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "/usr/local/include/mlx.h"

# define _USE_MATH_DEFINES

# define E_ARG "error: argument"
# define E_FILE "error: file"

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
// # define SCREEN_WIDTH 640
// # define SCREEN_HEIGHT 360

# define FOV_H 60
# define RAY_CNT 1280

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define MINIMAP_TILE 30
# define CHARACTER_SIZE 4

# define XPM_ROW 96
# define XPM_COL 96

# define KEY_ESC 53

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_M 46

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

typedef struct s_win {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	char	*dst;
	int		width;
	int		height;
}	t_win;

typedef struct s_player {
	double	x;
	double	y;
	double	speed;
	double	angle;
}	t_player;

#endif
