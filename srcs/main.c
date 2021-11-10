/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/07 16:32:25 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

void	rotate_player(t_vector *dir, float a)
{
	float	length;
	float	x;
	float	y;

	x = dir->x;
	y = dir->y;
	x = x * cosf(a) - y * sinf(a);
	y = x * sinf(a) + y * cosf(a);
	length = hypotf(x, y);
	dir->x = x / length;
	dir->y = y / length;
}

void	collision_check(t_vector *pos, t_vector delta, char **map)
{
	float	x;
	float	y;

	x = pos->x;
	y = pos->y;
	if (delta.x > 0
		&& map[(int)(y + delta.y)][(int)(x + delta.x + COL_SIZE)] == '1')
		x = ceilf(x) - COL_SIZE;
	else if (delta.x < 0
		&& map[(int)(y + delta.y)][(int)(x + delta.x - COL_SIZE)] == '1')
		x = floorf(x) + COL_SIZE;
	else
		x += delta.x;
	if (delta.y > 0
		&& map[(int)(y + delta.y + COL_SIZE)][(int)(x + delta.x)] == '1')
		y = ceilf(y) - COL_SIZE;
	else if (delta.y < 0
		&& map[(int)(y + delta.y - COL_SIZE)][(int)(x + delta.x)] == '1')
		y = floorf(y) + COL_SIZE;
	else
		y += delta.y;
	pos->x = x;
	pos->y = y;
}

void	move_player(t_player *player, char **map)
{
	t_vector	delta;

	if (player->move || player->strafe)
	{
		delta.x = ((float)(player->move) *player->dir.x
				+ (float)(player->strafe) *(-player->dir.y))
			* MOVE_SPEED * player->run;
		delta.y = ((float)(player->move) *player->dir.y
				+ (float)(player->strafe) *player->dir.x)
			* MOVE_SPEED * player->run;
		collision_check(&player->pos, delta, map);
	}
	if (player->rotate)
	{
		rotate_player(&player->dir, (float)player->rotate * ROT_SPEED);
		ft_plane(player);
	}
}


int	ft_check_p(t_map *map, t_opt *opt)
{
	(void)map;
	(void)opt;
	return (0);
}

void	set_moves(t_player *player, int keys)
{
	player->move = 0;
	player->strafe = 0;
	player->rotate = 0;
	player->run = 1;
	if (keys == 1)
		player->move++;
	if (keys == 2)
		player->move--;
	if (keys == 3)
		player->strafe++;
	if (keys == 4)
		player->strafe--;
	if (keys == 5)
		player->rotate++;
	if (keys == 6)
		player->rotate--;
	if (keys == 5 || keys == 6)
		player->run++;
}

/* Добавить free */
int	closer(void)
{
	exit(0);
}
int	key_press(int key, int *keys)
{
	if (key == W_KEY)
		*keys = 1;
	else if (key == S_KEY)
		*keys = 2;
	else if (key == D_KEY)
		*keys = 3;
	else if (key == A_KEY)
		*keys = 4;
	else if (key == RR_KEY)
		*keys = 5;
	else if (key == RL_KEY)
		*keys = 6;
	else if (key == ESC_KEY)
		closer();
	return (1);
}

int	key_release(int key, int *keys)
{
	if (key == W_KEY)
		*keys = 1;
	else if (key == S_KEY)
		*keys = 2;
	else if (key == D_KEY)
		*keys = 3;
	else if (key == A_KEY)
		*keys = 4;
	else if (key == RR_KEY)
		*keys = 5;
	else if (key == RL_KEY)
		*keys = 6;
	return (1);
}


void	mand_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->mand->addr + (y * opt->mand->line_length + x
			* (opt->mand->b_p_p / 8));
	*(unsigned int *)dst = color;
}

void	print_mandatori(t_opt *opt)
{
	int	x;
	int	y;

	y = 0;
	while (y < RES_Y)
	{
		x = 0;
		while (x < RES_X)
		{
			if (y > RES_Y * 0.5)
				mand_pixel_put(opt, x, y, opt->map->floor);
			else
				mand_pixel_put(opt, x, y, opt->map->sky);
			x++;
		}
		y++;
	}
}

int	draw_all(t_opt *opt)
{
	set_moves(opt->plr, opt->keys);
	move_player(opt->plr, opt->map->canvas);
	print_mandatori(opt);
	ft_draw_walls(opt);
	// lodev(opt);
	print_minimap(opt);
	mlx_put_image_to_window(opt->mlx, opt->win, opt->mand->img, 0, 0);
	opt->keys = 0;
	// mlx_do_sync(opt->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_opt	opt;

	if (argc != 2)
		puterror("incorrect arguments, need only one");
	ft_parcer(&opt, argv[1]);
	// opt.x_widht = -1;
	// opt.plr->pos_y = -1;
	print_minimap(&opt);
	// printf("x: %f	y: %f\n",  opt.x_widht, opt.plr->pos_y), exit(0);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_hook(opt.win, 2, 0, key_press, &opt.keys);
	// mlx_hook(opt.win, 3, 0, key_release, &opt.keys);
	mlx_loop_hook(opt.mlx, draw_all, &opt);
	mlx_loop(opt.mlx);
}
