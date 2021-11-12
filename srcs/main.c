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

int	key_press(int key, t_opt *opt)
{
	if (key == W_KEY)
		opt->keys->w = 1;
	else if (key == S_KEY)
		opt->keys->s = 1;
	else if (key == D_KEY)
		opt->keys->d = 1;
	else if (key == A_KEY)
		opt->keys->a = 1;
	else if (key == RL_KEY)
		opt->keys->arrow_l = 1;
	else if (key == RR_KEY)
		opt->keys->arrow_r = 1;
	if (key == ESC_KEY)
		exit(0);
	return (key);
}

int	key_release(int key, t_opt *opt)
{
	if (key == W_KEY)
		opt->keys->w = -1;
	else if (key == S_KEY)
		opt->keys->s = -1;
	else if (key == D_KEY)
		opt->keys->d = -1;
	else if (key == A_KEY)
		opt->keys->a = -1;
	else if (key == RL_KEY)
		opt->keys->arrow_l = -1;
	else if (key == RR_KEY)
		opt->keys->arrow_r = -1;
	return (key);
}

/* Добавить free */
int	closer(void)
{
	exit(0);
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
			if (y > opt->cnst->half_resY)
				my_mlx_pixel_put(opt, x, y, opt->map->floor);
			else
				my_mlx_pixel_put(opt, x, y, opt->map->sky);
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
	print_minimap(&opt);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_hook(opt.win, 2, 0, key_press, &opt);
	mlx_hook(opt.win, 3, 0, key_release, &opt);
	mlx_loop_hook(opt.mlx, draw_all, &opt);
	mlx_loop(opt.mlx);
}
