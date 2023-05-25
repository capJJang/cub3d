/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segan <segan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:58:57 by seyang            #+#    #+#             */
/*   Updated: 2023/05/25 20:15:44 by segan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	to_radian(double r)
{
	return (r * M_PI / 180);
}

t_win		*win;
t_player	*player;
char 		map[MAP_HEIGHT][MAP_WIDTH]=
	{
		{"111111111111111111111111"},
		{"100000000000000000000001"},
		{"1000000000000N0000000001"},
		{"100000000000000000000001"},
		{"100000222220000303030001"},
		{"100000200020000000000001"},
		{"100000200020000300030001"},
		{"100000200020000000000001"},
		{"100000220220000303030001"},
		{"100000000000000000000001"},
		{"100000000000000000000001"},
		{"100000000000000000000001"},
		{"100000000000000000000001"},
		{"100000000000000000000001"},
		{"100000000000000000000001"},
		{"100000000000000000000001"},
		{"144444444000000000000001"},
		{"120400004000000000000001"},
		{"120000504000000000000001"},
		{"120400004000000000000001"},
		{"120444444000000000000001"},
		{"120000000000000000000001"},
		{"124444444000000000000001"},
		{"111111111111111111111111"}
	};

void	set_player(t_win *win, t_player *player)
{
	for (int i = 0; i < CHARACTER_SIZE; i++)
	{
		for (int j = 0; j < CHARACTER_SIZE; j++)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, player->x + j, player->y + i, 0x0040FF);
		}
	}
}

int	get_color(int color, double distance)
{
	int	r;
	int	g;
	int	b;
	int	max_distance = MAP_HEIGHT * MINIMAP_TILE * 5 / 3;

	r = color % (16 * 16);
	g = color / (16 * 16) % (16 * 16);
	b = color / (16 * 16 * 16 * 16) % (16 * 16);
	r = r * (max_distance - distance) / max_distance;
	g = g * (max_distance - distance) / max_distance;
	b = b * (max_distance - distance) / max_distance;
	return (b * pow(16, 4) + g * pow(16, 2) + r);
}

void	ray(t_player *player, void *img)
{
	int		i;
	int		j;
	double	tan_pivot;
	int		to_draw;
	int		cnt = 1;
	int		tmp;
	double	k;
(void) img;

	tan_pivot = player->angle;
	printf("%f\n", player->angle);
// k -> ray의 각도 변화량 FOV_H(시야각) / RAY_CNT(쏠 ray의 양)으로 구함
	for (k = -1 * FOV_H / 2; k <= FOV_H / 2; k += (double)FOV_H / (double)RAY_CNT)
	{

	// (i, j) -> ray의 시작지점
		i = player->y + floor(CHARACTER_SIZE / 2);
		j = player->x + floor(CHARACTER_SIZE / 2);
		while (1)
		{
		// angle 범위 -45 ~ 45
			if (tan_pivot + k < 45 || tan_pivot + k >= 270 + 45)
			{
				j++;
				i = player->y + floor(CHARACTER_SIZE / 2) - tan(to_radian(tan_pivot + k)) * fabs(player->x + floor(CHARACTER_SIZE / 2) - j);
			}
		// 45 ~ 135
			else if (tan_pivot + k < 90 + 45)
			{
				i--;
				j = player->x + floor(CHARACTER_SIZE / 2) - tan(to_radian(tan_pivot + k - 90)) * fabs(player->y + floor(CHARACTER_SIZE / 2) - i);
			}
		// 135 ~ 225
			else if (tan_pivot + k < 180 + 45)
			{
				j--;
				i = player->y + floor(CHARACTER_SIZE / 2) + tan(to_radian(tan_pivot + k - 180)) * fabs(player->x + floor(CHARACTER_SIZE / 2) - j);
			}
		// 225 ~ 315(-45)
			else if (tan_pivot + k < 270 + 45)
			{
				i++;
				j = player->x + floor(CHARACTER_SIZE / 2) + tan(to_radian(tan_pivot + k - 270)) * fabs(player->y + floor(CHARACTER_SIZE / 2) - i);
			}
		// ray가 벽에 닿으면 break
			if (map[i / MINIMAP_TILE][j / MINIMAP_TILE] != '0')
				break ;
		}
		// to_draw -> 그려야하는 세로픽셀의 양
		to_draw = 5 * (double)SCREEN_HEIGHT / ((double)2 * sqrt(pow(player->x + floor(CHARACTER_SIZE / 2) - j, 2) + pow(player->y + floor(CHARACTER_SIZE / 2) - i, 2)) * cos(to_radian(k)) * tan(to_radian((double)SCREEN_HEIGHT / (double)SCREEN_WIDTH * (double)FOV_H / (double)2)));
		// m -> to_draw 만큼 반복하며 세로 그리기
		for (int m = 0; m < to_draw; m++)
		{
			// n -> SCREEN_WIDTH(가로해상도) / RAY_CNT(쏘는 ray의 개수)만큼 반복하며 가로 그리기
			for (int n = 0; n < SCREEN_WIDTH / RAY_CNT ; n++)
			{
				// 벽의 종류에 따라 다르게 그리기
				if (map[i / MINIMAP_TILE][j / MINIMAP_TILE] == '1')
				{
					// get_color 함수 : 거리에 따른 명암조절
					// mlx_get_addr로 img파일의 정보를 배열로 바꾼 후, 몇번째 index를 가져와 그릴지 계산해야되는데 seg..가 종종 뜸
					mlx_pixel_put(win->mlx_ptr, win->win_ptr, n + SCREEN_WIDTH - (cnt * (SCREEN_WIDTH / RAY_CNT)), (SCREEN_HEIGHT - to_draw) / 2 + m, get_color(((int*)mlx_get_data_addr(img, &tmp, &tmp, &tmp))[(96 * (95 * m / to_draw)) + ((int)((i - player->y + floor(CHARACTER_SIZE / 2)) / tan(to_radian(tan_pivot + k)) + player->x + floor(CHARACTER_SIZE / 2))) % MINIMAP_TILE * 96 / MINIMAP_TILE], (double)2 * sqrt(pow(player->x + 2 - j, 2) + pow(player->y + 2 - i, 2))));
				}
				else if (map[i / MINIMAP_TILE][j / MINIMAP_TILE] == '2')
					mlx_pixel_put(win->mlx_ptr, win->win_ptr, n + SCREEN_WIDTH - (cnt * (SCREEN_WIDTH / RAY_CNT)), (SCREEN_HEIGHT - to_draw) / 2 + m, get_color(0xDF3A01, (double)2 * sqrt(pow(player->x + 2 - j, 2) + pow(player->y + 2 - i, 2))));
				else if (map[i / MINIMAP_TILE][j / MINIMAP_TILE] == '3')
					mlx_pixel_put(win->mlx_ptr, win->win_ptr, n + SCREEN_WIDTH - (cnt * (SCREEN_WIDTH / RAY_CNT)), (SCREEN_HEIGHT - to_draw) / 2 + m, get_color(0x04B431, (double)2 * sqrt(pow(player->x + 2 - j, 2) + pow(player->y + 2 - i, 2))));
				else if (map[i / MINIMAP_TILE][j / MINIMAP_TILE] == '4')
					mlx_pixel_put(win->mlx_ptr, win->win_ptr, n + SCREEN_WIDTH - (cnt * (SCREEN_WIDTH / RAY_CNT)), (SCREEN_HEIGHT - to_draw) / 2 + m, get_color(0xFE2EC8, (double)2 * sqrt(pow(player->x + 2 - j, 2) + pow(player->y + 2 - i, 2))));
			}
		}
		cnt++;
	}
}

void	get_player_info(char map[MAP_WIDTH][MAP_HEIGHT], t_player *player)
{
	player->speed = 1;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j] == 'N')
			{
				player->x = j * MINIMAP_TILE + MINIMAP_TILE / 2;
				player->y = i * MINIMAP_TILE + MINIMAP_TILE / 2;
				map[i][j] = '0';
				player->angle = 90;
			}
		}
	}
}

void clear_screen()
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
}

void	show_minimap(t_player *player)
{
	// MINIMAP_TILE -> 벽 하나당 그릴 픽셀크기
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j] == '0' || map[i][j] == 'N')
			{
				for (int k = 0; k < MINIMAP_TILE; k++)
				{
					for (int l = 0; l < MINIMAP_TILE; l++)
					{
						mlx_pixel_put(win->mlx_ptr, win->win_ptr, j * MINIMAP_TILE + k, i * MINIMAP_TILE + l, 0xFFFFFF);
					}
				}
			}
			else
			{
				for (int k = 0; k < MINIMAP_TILE; k++)
				{
					for (int l = 0; l < MINIMAP_TILE; l++)
					{
						mlx_pixel_put(win->mlx_ptr, win->win_ptr, j * MINIMAP_TILE + k, i * MINIMAP_TILE + l, 0x8000FF);
					}
				}
			}
		}
	}

	int		i;
	int		j;
	double	tan_pivot;

	i = player->y + floor(CHARACTER_SIZE / 2);
	j = player->x + floor(CHARACTER_SIZE / 2);
	tan_pivot = player->angle;
	for (double k = -1 * FOV_H / 2; k <= FOV_H / 2; k += (double)FOV_H / (double)RAY_CNT)
	{
		i = player->y + floor(CHARACTER_SIZE / 2);
		j = player->x + floor(CHARACTER_SIZE / 2);
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, j, i, 0xFF0000);
		while (1)
		{
			if (tan_pivot + k <= 45 || tan_pivot + k > 270 + 45)
			{
				j++;
				if (tan_pivot + k == 45)
					i--;
				else
					i = player->y + floor(CHARACTER_SIZE / 2) - tan(to_radian(tan_pivot + k)) * fabs(player->x + floor(CHARACTER_SIZE / 2) - j);
			}
			else if (tan_pivot + k <= 90 + 45)
			{
				i--;
				if (tan_pivot + k == 90 + 45)
					j--;
				else
					j = player->x + floor(CHARACTER_SIZE / 2) - tan(to_radian(tan_pivot + k - 90)) * fabs(player->y + floor(CHARACTER_SIZE / 2) - i);
			}
			else if (tan_pivot + k <= 180 + 45)
			{
				j--;
				if (tan_pivot + k == 180 + 45)
					i++;
				else
					i = player->y + floor(CHARACTER_SIZE / 2) + tan(to_radian(tan_pivot + k - 180)) * fabs(player->x + floor(CHARACTER_SIZE / 2) - j);
			}
			else if (tan_pivot + k <= 270 + 45)
			{
				i++;
				if (tan_pivot + k == 270 + 45)
					j++;
				else
					j = player->x + floor(CHARACTER_SIZE / 2) + tan(to_radian(tan_pivot + k - 270)) * fabs(player->y + floor(CHARACTER_SIZE / 2) - i);
			}
			if (map[i / MINIMAP_TILE][j / MINIMAP_TILE] != '0')
				break ;
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, j, i, 0xFF0000);
			// set_player(win, player);
		}
	}
}

void	rendering(t_player *player, int keycode, void *img)
{
	(void) keycode;
	(void) player;
	clear_screen();
// raycasting
	ray(player, img);
// M키 누르면 미니맵
	if (keycode == KEY_M)
		show_minimap(player);

}

int	key_press(int keycode, void *img)
{
	double	x;
	double	y;

// x, y 초기위치 임시저장
	x = player->x;
	y = player->y;
	if (keycode == KEY_ESC)
		exit (0);
// 플레이어 이동 방향키
	if (keycode == KEY_D)
	{
		player->x -= player->speed * cos(to_radian(player->angle + 90));
		player->y += player->speed * sin(to_radian(player->angle + 90));
	}
	else if (keycode == KEY_A)
	{
		player->x -= player->speed * cos(to_radian(player->angle - 90));
		player->y += player->speed * sin(to_radian(player->angle - 90));
	}
	else if (keycode == KEY_S)
	{
		player->x -= player->speed * cos(to_radian(player->angle));
		player->y += player->speed * sin(to_radian(player->angle));
	}
	else if (keycode == KEY_W)
	{
		player->x += player->speed * cos(to_radian(player->angle));
		player->y -= player->speed * sin(to_radian(player->angle));
	}
// 플레이어 시선 방향키
	if (keycode == KEY_LEFT)
		player->angle += 3;
	else if (keycode == KEY_RIGHT)
		player->angle -= 3;
// 360도 범위 내
	if (player->angle > 360)
		player->angle -= 360;
	else if (player->angle < 0)
		player->angle += 360;
// 움직인 곳이 벽이면 원래값으로 돌려놓음
	if (map[(int)((player->y + CHARACTER_SIZE) / MINIMAP_TILE)][(int)((player->x + CHARACTER_SIZE) / MINIMAP_TILE)] != '0' || \
		map[(int)((player->y - 1) / MINIMAP_TILE)][(int)((player->x + CHARACTER_SIZE) / MINIMAP_TILE)] != '0' || \
		map[(int)((player->y + CHARACTER_SIZE) / MINIMAP_TILE)][(int)((player->x - 1) / MINIMAP_TILE)] != '0' || \
		map[(int)((player->y - 1) / MINIMAP_TILE)][(int)((player->x - 1) / MINIMAP_TILE)] != '0')
		{
			player->x = x;
			player->y = y;
		}
	// printf("%d\n", keycode);
// rendering
	rendering(player, keycode, img);
	return (0);
}

int	test(void *test)
{
	(void) test;
	exit (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	// if (argc != 2)
	// 	return (print_err(E_ARG));
	// else if (invalid_file(argv))
	// 	return (print_err(E_FILE));
int	i;

// 윈도우 초기화
	win = malloc(sizeof(t_win));
	if (win == NULL)
		exit (1);
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, \
		"cub3d");
// xpm 파일 로드
	void	*img = mlx_xpm_file_to_image(win->mlx_ptr, \
			"./texture/Dungeons-Walls-_1_.xpm", &i, &i);
// player 초기화
	player = malloc(sizeof(t_player));
	if (player == NULL)
		exit (1);
	get_player_info(map, player);
// rendering
	rendering(player, 0, img);
// 2번째 인자 '2' -> 연속키입력
	mlx_hook(win->win_ptr, 2, 0, key_press, img);
// x(red cross) 종료
	mlx_hook(win->win_ptr, 17, 0, test, 0);
	mlx_loop(win->mlx_ptr);
}
