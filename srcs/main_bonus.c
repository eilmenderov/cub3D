/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:49:50 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 11:49:51 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

int	closer(t_opt *opt)
{
	ft_free_split(opt->map->canvas);
	free(opt->map->path_n);
	free(opt->map->path_s);
	free(opt->map->path_w);
	free(opt->map->path_e);
	free(opt->map);
	free(opt->plr);
	free(opt->cnst);
	free(opt->mand);
	free(opt->pic->wall_n);
	free(opt->pic->wall_s);
	free(opt->pic->wall_w);
	free(opt->pic->wall_e);
	free(opt->pic);
	mlx_destroy_window(opt->mlx, opt->win);
	exit(0);
}

void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->mand->addr + (y * opt->mand->line_length + x
			* opt->cnst->b_p_p_del);
	*(unsigned int *)dst = color;
}

static void	print_mandatori(t_opt *opt)
{
	int	x;
	int	y;

	y = 0;
	while (y < RES_Y)
	{
		x = 0;
		while (x < RES_X)
		{
			if (y > opt->cnst->half_resy)
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_opt	opt;

	if (argc != 2)
		puterror("incorrect arguments, need only one");
	ft_parcer(&opt, argv[1]);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_hook(opt.win, 2, 0, key_press, &opt);
	mlx_hook(opt.win, 3, 0, key_release, &opt);
	mlx_loop_hook(opt.mlx, draw_all, &opt);
	mlx_loop(opt.mlx);
}
