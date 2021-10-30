/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/10/30 17:24:44 by fcarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

void	puterror(char *errorline)
{
	ft_putendl_fd(errorline, 1);
	exit(1);
}

void	parse_map(t_opt *opt)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = *opt->lst;
	opt->map->canvas = malloc(sizeof(char *) * ft_lstsize(lst));
	if (!opt->map->canvas)
		exit(0);
	while (lst)
	{
		opt->map->canvas[i] = lst->content;
		lst = lst->next;
		i++;
	}
	opt->map->canvas[i] = NULL;
}

void	read_map(t_opt *opt, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	ft_gnl_old(fd, &line);
	*(opt->lst) = ft_lstnew(line);
	while (ft_gnl_old(fd, &line))
		ft_lstadd_back(opt->lst, ft_lstnew(line));
	ft_lstadd_back(opt->lst, ft_lstnew(line));
	parse_map(opt);
}

int	keyhook(int key, t_opt *opt)
{
	if (key == 53)
		exit(0);
	(void)opt;
	return (key);
}

void	fillopt(t_opt *opt)
{
	opt->x_widht = PIC_SIZE;
	opt->y_heidht = PIC_SIZE;
}

void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->addr + (y * opt->line_length + x * (opt->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

	fillopt(&opt);
	if (argc != 2)
		puterror("Map error");
	opt.map = malloc(sizeof(t_map));
	opt.pic = malloc(sizeof(t_pic));
	opt.lst = malloc(sizeof(t_list *));
	read_map(&opt, argv[1]);
	opt.mlx = mlx_init();
	opt.win = mlx_new_window(opt.mlx, RES_X, RES_Y, "cub3d");
	opt.img = mlx_new_image(opt.mlx, RES_X, RES_Y);
	opt.addr = mlx_get_data_addr(opt.img, &opt.bits_per_pixel, &opt.line_length, &opt.endian);
	printmap(&opt);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img, 20, 20);
	mlx_key_hook(opt.win, keyhook, &opt);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_loop(opt.mlx);
}
