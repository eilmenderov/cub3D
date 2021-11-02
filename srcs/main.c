/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/02 17:16:10 by fcarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

int	keyhook(int key, t_opt *opt)
{
	int	step;

	step = (int)PIC_SIZE * 0.05;
	if (key == W_KEY && opt->y_heidht > PIC_SIZE)
	{
		printf("forwad   key: %d\n", key);
		if (opt->map->canvas[(int)((opt->y_heidht - 10) / PIC_SIZE)][(int)((opt->x_widht - 5) / PIC_SIZE)] != '1')
			opt->y_heidht -= step, printf("w_x: %f	w_y: %f\n", opt->x_widht, opt->y_heidht);
	}
	if (key == A_KEY && opt->x_widht > PIC_SIZE)
	{
		printf("left     key: %d\n", key);
		if (opt->map->canvas[(int)((opt->y_heidht - 5) / PIC_SIZE)][(int)((opt->x_widht - 10) / PIC_SIZE)] != '1')
			opt->x_widht -= step, printf("a_x: %f	a_y: %f\n", opt->x_widht, opt->y_heidht);
	}
	if (key == S_KEY)
	{
		printf("backward key: %d\n", key);
		if (opt->map->canvas[(int)((opt->y_heidht) / PIC_SIZE)][(int)((opt->x_widht - 5) / PIC_SIZE)] != '1')
			opt->y_heidht += step, printf("s_x: %f	s_y: %f\n", opt->x_widht, opt->y_heidht);
	}
	if (key == D_KEY)
	{
		printf("right    key: %d\n", key);
		if (opt->map->canvas[(int)((opt->y_heidht - 5) / PIC_SIZE)][(int)((opt->x_widht) / PIC_SIZE)] != '1')
			opt->x_widht += step, printf("d_x: %f	d_y: %f\n", opt->x_widht, opt->y_heidht);
	}
	if (key == RL_KEY)
		opt->angle -= M_PI / 180;
	if (key == RR_KEY)
		opt->angle += M_PI / 180;
	if (key == 53)
		exit(0);
	printmap(opt);
	mlx_put_image_to_window(opt->mlx, opt->win, opt->img, DELTA, DELTA);
	return (key);
}

int	closer(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_opt	opt;

	if (argc != 2)
		puterror("incorrect arguments, need only one");
	ft_parcer(&opt, argv[1]);
	opt.x_widht = -1;
	opt.y_heidht = -1;
	printmap(&opt);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img, DELTA, DELTA);
	// printf("x: %d	y: %d\n", opt.x_widht, opt.y_heidht);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_hook(opt.win, 2, 1L<<0, keyhook, &opt);
	mlx_loop(opt.mlx);
}
