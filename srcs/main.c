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

int	ft_check_p(t_map *map, t_opt *opt)
{
	(void)map;
	(void)opt;
	return (0);
}

int	keyhook(int key, t_opt *opt)
{
	float	step;

	step = MOVE_SPEED;
	if (key == W_KEY && !ft_check_p(opt->map, opt))
	{
		opt->plr->pos_y += (step * sin(opt->plr->angle));
		opt->plr->pos_x += (step * cos(opt->plr->angle));
	}
	if (key == A_KEY && !ft_check_p(opt->map, opt))
	{
		opt->plr->pos_y -= (step * sin(opt->plr->angle + M_PI_2));
		opt->plr->pos_x -= (step * cos(opt->plr->angle + M_PI_2));
	}
	if (key == S_KEY && !ft_check_p(opt->map, opt))
	{
		opt->plr->pos_y -= (step * sin(opt->plr->angle));
		opt->plr->pos_x -= (step * cos(opt->plr->angle));
	}
	if (key == D_KEY && !ft_check_p(opt->map, opt))
	{
		opt->plr->pos_y += (step * sin(opt->plr->angle + M_PI_2));
		opt->plr->pos_x += (step * cos(opt->plr->angle + M_PI_2));
	}
	if (key == RL_KEY)
		opt->plr->angle -= M_PI / ROT_SPEED;
	if (key == RR_KEY)
		opt->plr->angle += M_PI / ROT_SPEED;
	if (key == 53)
		exit(0);
	return (key);
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
	print_mandatori(opt);
	ft_draw_walls(opt);
	// lodev(opt);
	print_minimap(opt);
	mlx_put_image_to_window(opt->mlx, opt->win, opt->mand->img, 0, 0);
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
	mlx_hook(opt.win, 2, 1L << 0, keyhook, &opt);
	mlx_loop_hook(opt.mlx, draw_all, &opt);
	mlx_loop(opt.mlx);
}
