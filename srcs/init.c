/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:25:21 by vleida            #+#    #+#             */
/*   Updated: 2021/11/05 18:07:40 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

static void	ft_init_opt_map(t_opt *opt)
{
	opt->pic->opt = opt;
	opt->map->opt = opt;
	opt->x_widht = PIC_SIZE;
	opt->y_heidht = PIC_SIZE;
	opt->angle = 0;
	opt->map->canvas = NULL;
	opt->map->path_n = NULL;
	opt->map->path_s = NULL;
	opt->map->path_w = NULL;
	opt->map->path_e = NULL;
	opt->map->floor = -1;
	opt->map->sky = -1;
	opt->map->viewpos = 0;
	opt->map->flag = 0;
}

static void	ft_init_images(t_opt *opt)
{
	opt->mand = malloc(sizeof(t_img));
	if (!opt->mand)
		puterror("can't allocate memory(img)");
	opt->mand->img = mlx_new_image(opt->mlx, RES_X, RES_Y);
	if (!opt->mand->img)
		puterror("can't create new image");
	opt->mand->addr = mlx_get_data_addr(opt->mand->img, &opt->mand->b_p_p,
			&opt->mand->line_length, &opt->mand->endian);
	if (!opt->mand->addr)
		puterror("can't create image addr");
	opt->minimap = malloc(sizeof(t_img));
	if (!opt->minimap)
		puterror("can't allocate memory(img)");
	opt->minimap->img = mlx_new_image(opt->mlx, RES_X * 0.26, RES_Y * 0.2);
	if (!opt->minimap->img)
		puterror("can't create new image");
	opt->minimap->addr = mlx_get_data_addr(opt->minimap->img,
			&opt->minimap->b_p_p, &opt->minimap->line_length,
			&opt->minimap->endian);
	if (!opt->minimap->addr)
		puterror("can't create image addr");
}

void	ft_init_structs(t_opt *opt)
{
	opt->map = malloc(sizeof(t_map));
	if (!opt->map)
		puterror("can't allocate memory(map)");
	opt->pic = malloc(sizeof(t_pic));
	if (!opt->pic)
		puterror("can't allocate memory(pic)");
	opt->mlx = mlx_init();
	if (!opt->mlx)
		puterror("can't initialize mlx");
	opt->win = mlx_new_window(opt->mlx, RES_X, RES_Y, "cub3d");
	if (!opt->win)
		puterror("can't create game window");
	ft_init_images(opt);
	ft_init_opt_map(opt);
}