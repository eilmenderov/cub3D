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

int	keypress(int key, t_opt *opt)
{
	double	step_x;
	double	step_y;

	step_x = opt->plr->dir.x * MOVE_SPEED;
	step_y = opt->plr->dir.y * MOVE_SPEED;
	if (key == W_KEY)
	{
		if(!ft_check_p(opt->map, opt, step_x, 0))
			opt->plr->pos.x += step_x;
		if(!ft_check_p(opt->map, opt, 0, step_y))
			opt->plr->pos.y += step_y;
	}
	if (key == S_KEY)
	{
		if(!ft_check_p(opt->map, opt, -step_x, 0))
			opt->plr->pos.x -= step_x;
		if(!ft_check_p(opt->map, opt, 0, -step_y))
			opt->plr->pos.y -= step_y;
	}
	// if (key == D_KEY)
	// {
	// 	opt->plr->pos.y += (step * sin(opt->plr->angle));
	// 	opt->plr->pos.x += (step * cos(opt->plr->angle));
	// }
	// if (key == A_KEY && !ft_check_p(opt->map, opt))
	// {
	// 	opt->plr->pos.y -= (step * sin(opt->plr->angle));
	// 	opt->plr->pos.x -= (step * cos(opt->plr->angle));
	// }
	if (key == RL_KEY)
	{
		opt->plr->dir.x = opt->plr->dir.x * cos(-ROT_SPEED) - opt->plr->dir.y * sin(-ROT_SPEED);
		opt->plr->dir.y = opt->plr->dir.x * sin(-ROT_SPEED) + opt->plr->dir.y * cos(-ROT_SPEED);
		double	length = hypot(opt->plr->dir.x, opt->plr->dir.y);
		opt->plr->dir.x = opt->plr->dir.x / length;
		opt->plr->dir.y = opt->plr->dir.y / length;
	}
	if (key == RR_KEY)
	{
		opt->plr->dir.x = opt->plr->dir.x * cos(ROT_SPEED) - opt->plr->dir.y * sin(ROT_SPEED);
		opt->plr->dir.y = opt->plr->dir.x * sin(ROT_SPEED) + opt->plr->dir.y * cos(ROT_SPEED);
		double	length = hypot(opt->plr->dir.x, opt->plr->dir.y);
		opt->plr->dir.x = opt->plr->dir.x / length;
		opt->plr->dir.y = opt->plr->dir.y / length;
	}
	ft_plane(opt->plr);
	if (key == 53)
		exit(0);
	return (key);
}

// int	keyrelease(int key, t_opt *opt)
// {
// 	float	step;

// 	step = MOVE_SPEED;
// 	if (key == W_KEY && !ft_check_p(opt->map, opt))
// 	{
// 		if(opt->map->canvas[(int)(opt->plr->pos.x + opt->plr->dir.x * MOVE_SPEED)][(int)(opt->plr->pos.y)] == '0')
// 			opt->plr->pos.x += opt->plr->dir.x * MOVE_SPEED;
// 		if(opt->map->canvas[(int)(opt->plr->pos.x)][(int)(opt->plr->pos.y + opt->plr->dir.y * MOVE_SPEED)] == '0')
// 			opt->plr->pos.y += opt->plr->dir.y * MOVE_SPEED;
// 	}
// 	if (key == A_KEY && !ft_check_p(opt->map, opt))
// 	{
// 		opt->plr->pos.y -= (step * sin(opt->plr->angle + M_PI_2));
// 		opt->plr->pos.x -= (step * cos(opt->plr->angle + M_PI_2));
// 	}
// 	if (key == S_KEY && !ft_check_p(opt->map, opt))
// 	{
// 		opt->plr->pos.y -= (step * sin(opt->plr->angle));
// 		opt->plr->pos.x -= (step * cos(opt->plr->angle));
// 	}
// 	if (key == D_KEY && !ft_check_p(opt->map, opt))
// 	{
// 		opt->plr->pos.y += (step * sin(opt->plr->angle + M_PI_2));
// 		opt->plr->pos.x += (step * cos(opt->plr->angle + M_PI_2));
// 	}
// 	if (key == RL_KEY)
// 		opt->plr->angle -= M_PI / ROT_SPEED;
// 	if (key == RR_KEY)
// 		opt->plr->angle += M_PI / ROT_SPEED;
// 	if (key == 53)
// 		exit(0);
// 	return (key);
// }

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
	mlx_hook(opt.win, 2, 1L << 0, keypress, &opt);
	// mlx_hook(opt.win, 3, 1L << 0, keyrelease, &opt);
	mlx_loop_hook(opt.mlx, draw_all, &opt);
	mlx_loop(opt.mlx);
}
