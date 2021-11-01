/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/01 17:17:15 by fcarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

int	keyhook(int key, t_opt *opt)
{
	mlx_put_image_to_window(opt->mlx, opt->win, opt->img, 20, 20);
	if (key == 13 && opt->y_heidht > PIC_SIZE)
	{
		printf("forwad key: %d\n", key);
		if (opt->map->canvas[(opt->y_heidht - 10) / PIC_SIZE][(opt->x_widht - 5) / PIC_SIZE] != '1')
			opt->y_heidht -= 5;
	}
	if (key == 0 && opt->x_widht > PIC_SIZE)
	{
		printf("left key: %d\n", key);
		if (opt->map->canvas[(opt->y_heidht - 5) / PIC_SIZE][(opt->x_widht - 10) / PIC_SIZE] != '1')
			opt->x_widht -= 5;
	}
	if (key == 1)
	{
		printf("backward key: %d\n", key);
		if (opt->map->canvas[(opt->y_heidht) / PIC_SIZE][(opt->x_widht - 5) / PIC_SIZE] != '1')
			opt->y_heidht += 5;
	}
	if (key == 2)
	{
		printf("right key: %d\n", key);
		if (opt->map->canvas[(opt->y_heidht - 5) / PIC_SIZE][(opt->x_widht) / PIC_SIZE] != '1')
			opt->x_widht += 5;
	}
	if (key == 53)
		exit(0);
	mlx_put_image_to_window(opt->mlx, opt->win, opt->img, 20, 20);
	printmap(opt);
	(void)opt;
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
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img, 20, 20);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_hook(opt.win, 2, 1L<<0, keyhook, &opt);
	mlx_loop(opt.mlx);
}
