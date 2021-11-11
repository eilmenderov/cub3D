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

int	ft_check_p(t_map *map, t_opt *opt, double x, double y)
{
	x = opt->plr->pos.x + x;
	y = opt->plr->pos.y + y;
	if (map->canvas[(int)y][(int)x] != '1')
		return (0);
	return (1);
}

int	key_press(int key, t_opt *opt)
{
	double	step_x;
	double	step_y;

	step_x = opt->plr->dir.x * MOVE_SPEED;
	step_y = opt->plr->dir.y * MOVE_SPEED;
	if (key == W_KEY)
		opt->keys = 1;
	else if (key == S_KEY)
		opt->keys = 2;
	else if (key == D_KEY)
		opt->keys = 3;
	else if (key == A_KEY)
		opt->keys = 4;
	else if (key == RL_KEY)
		opt->keys = 5;
	else if (key == RR_KEY)
		opt->keys = 6;
	if (key == ESC_KEY)
		exit(0);
	return (key);
}

int	key_release(int key, t_opt *opt)
{
	double	step_x;
	double	step_y;

	step_x = opt->plr->dir.x * MOVE_SPEED;
	step_y = opt->plr->dir.y * MOVE_SPEED;
	if (key == W_KEY)
		opt->keys = 1;
	else if (key == S_KEY)
		opt->keys = 2;
	else if (key == D_KEY)
		opt->keys = 3;
	else if (key == A_KEY)
		opt->keys = 4;
	else if (key == RL_KEY)
		opt->keys = 5;
	else if (key == RR_KEY)
		opt->keys = 6;
	return (key);
}


void	move_player(t_opt *opt)
{
	double	step_x;
	double	step_y;

	step_x = opt->plr->dir.x * MOVE_SPEED;
	step_y = opt->plr->dir.y * MOVE_SPEED;
	if (opt->keys == 1)
	{
		if(!ft_check_p(opt->map, opt, step_x, 0))
			opt->plr->pos.x += step_x;
		if(!ft_check_p(opt->map, opt, 0, step_y))
			opt->plr->pos.y += step_y;
	}
	if (opt->keys == 2)
	{
		if(!ft_check_p(opt->map, opt, -step_x, 0))
			opt->plr->pos.x -= step_x;
		if(!ft_check_p(opt->map, opt, 0, -step_y))
			opt->plr->pos.y -= step_y;
	}
	if (opt->keys == 3)
	{
		if(!ft_check_p(opt->map, opt, 0, step_x))
			opt->plr->pos.y += (step_x);
		if(!ft_check_p(opt->map, opt, -step_y, 0))
			opt->plr->pos.x -= (step_y);
	}
	if (opt->keys == 4)
	{
		if(!ft_check_p(opt->map, opt, 0, -step_x))
			opt->plr->pos.y -= (step_x);
		if(!ft_check_p(opt->map, opt, step_y, 0))
			opt->plr->pos.x += (step_y);
	}
	if (opt->keys == 5)
	{
		opt->plr->dir.x = opt->plr->dir.x * cos(-ROT_SPEED) - opt->plr->dir.y * sin(-ROT_SPEED);
		opt->plr->dir.y = opt->plr->dir.x * sin(-ROT_SPEED) + opt->plr->dir.y * cos(-ROT_SPEED);
		double	length = hypot(opt->plr->dir.x, opt->plr->dir.y);
		opt->plr->dir.x = opt->plr->dir.x / length;
		opt->plr->dir.y = opt->plr->dir.y / length;
		ft_plane(opt->plr);
		opt->plr->angle += -ROT_SPEED;
	}
	if (opt->keys == 6)
	{
		opt->plr->dir.x = opt->plr->dir.x * cos(ROT_SPEED) - opt->plr->dir.y * sin(ROT_SPEED);
		opt->plr->dir.y = opt->plr->dir.x * sin(ROT_SPEED) + opt->plr->dir.y * cos(ROT_SPEED);
		double	length = hypot(opt->plr->dir.x, opt->plr->dir.y);
		opt->plr->dir.x = opt->plr->dir.x / length;
		opt->plr->dir.y = opt->plr->dir.y / length;
		ft_plane(opt->plr);
		opt->plr->angle += ROT_SPEED;
	}
	opt->old_keys = opt->keys;
	opt->keys = -1;
}

/* Добавить free */
int	closer(void)
{
	exit(0);
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
	move_player(opt);
	print_mandatori(opt);
	ft_draw_walls(opt);
	print_minimap(opt);
	mlx_put_image_to_window(opt->mlx, opt->win, opt->mand->img, 0, 0);
	// opt->keys = -1;
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
	mlx_hook(opt.win, 2, 0, key_press, &opt);
	mlx_hook(opt.win, 3, 0, key_release, &opt.keys);
	mlx_loop_hook(opt.mlx, draw_all, &opt);
	mlx_loop(opt.mlx);
}
