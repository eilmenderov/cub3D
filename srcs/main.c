/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/10/31 14:56:25 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

int	keyhook(int key, t_opt *opt)
{
	if (key == 53)
		exit(0);
	(void)opt;
	return (key);
}

void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->addr + (y * opt->line_length + x * (opt->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	closer(void)
{
	exit(0);
}

void	sizepixel(t_opt *opt, int x, int y, int color)
{
	int	x_size;
	int	y_size;

	y_size = y - PIC_SIZE;
	while (y_size < y && y_size < RES_Y)
	{
		x_size = x - PIC_SIZE;
		while (x_size < x && x_size < RES_X)
		{
			my_mlx_pixel_put(opt, x_size, y_size, color);
			x_size++;
		}
		y_size++;
	}
}

void	printmap(t_opt *opt)
{
	int	x;
	int	y;	

	y = 0;
	x = 0;
	while (opt->map->canvas[y])
	{
		x = 0;
		opt->x_widht = PIC_SIZE;
		while (opt->map->canvas[y][x])
		{
			if (opt->map->canvas[y][x] == '1')
				sizepixel(opt, opt->x_widht, opt->y_heidht, 0xFFFFFF);
			else if (opt->map->canvas[y][x] == '0')
				sizepixel(opt, opt->x_widht, opt->y_heidht, 0x708090);
			else if (opt->map->canvas[y][x] == 'N')
				sizepixel(opt, opt->x_widht, opt->y_heidht, 0xFF0000);
			x++;
			opt->x_widht += PIC_SIZE;
		}
		opt->y_heidht += PIC_SIZE;
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_opt	opt;

	if (argc != 2)
		puterror("incorrect arguments, need only one");
	ft_parcer(&opt, argv[1]);
	printmap(&opt);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img, 20, 20);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_key_hook(opt.win, keyhook, &opt);
	mlx_loop(opt.mlx);
}
