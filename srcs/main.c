/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/05 18:21:03 by vleida           ###   ########.fr       */
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
	int	step;

	step = (int)MAP_SIZE * MOVE_SPEED;
	if (key == W_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht += (step * sin(opt->angle));
		opt->x_widht += (step * cos(opt->angle));
	}
	if (key == A_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht -= (step * sin(opt->angle + M_PI_2));
		opt->x_widht -= (step * cos(opt->angle + M_PI_2));
	}
	if (key == S_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht -= (step * sin(opt->angle));
		opt->x_widht -= (step * cos(opt->angle));
	}
	if (key == D_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht += (step * sin(opt->angle + M_PI_2));
		opt->x_widht += (step * cos(opt->angle + M_PI_2));
	}
	if (key == RL_KEY)
		opt->angle -= M_PI / ROT_SPEED;
	if (key == RR_KEY)
		opt->angle += M_PI / ROT_SPEED;
	if (key == 53)
		exit(0);
	sizepixel_player(opt, (int)opt->x_widht, (int)opt->y_heidht, 0xFF0000);
	print_minimap(opt);
	mlx_put_image_to_window(opt->mlx, opt->win, opt->minimap->img, DELTA, DELTA);
	printf("key: %d	w_x: %f	w_y: %f angle: %f\n", key, opt->x_widht, opt->y_heidht, opt->angle);
	return (key);
}

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
			if (x < RES_X * 0.267 && y < RES_Y * 0.207)
				mand_pixel_put(opt, x, y, 0);
			else if (y > RES_Y * 0.5)
				mand_pixel_put(opt, x, y, opt->map->floor);
			else
				mand_pixel_put(opt, x, y, opt->map->sky);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_opt	opt;

	if (argc != 2)
		puterror("incorrect arguments, need only one");
	ft_parcer(&opt, argv[1]);
	opt.x_widht = -1;
	opt.y_heidht = -1;
	print_mandatori(&opt);
	print_minimap(&opt);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.mand->img, 0, 0);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.minimap->img, DELTA, DELTA);
	// printf("x: %d	y: %d\n", opt.x_widht, opt.y_heidht);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_hook(opt.win, 2, 1L<<0, keyhook, &opt);
	mlx_loop(opt.mlx);
}
