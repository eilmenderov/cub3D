/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:25:21 by vleida            #+#    #+#             */
/*   Updated: 2021/11/07 13:28:33 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

static void	ft_init_opt_map(t_opt *opt)
{
	opt->pic->opt = opt;
	opt->map->opt = opt;
	opt->plr->pos.x = PIC_SIZE;
	opt->plr->pos.y = PIC_SIZE;
	opt->plr->angle = 0;
	opt->plr->opt = opt;
	opt->map->canvas = NULL;
	opt->map->path_n = NULL;
	opt->map->path_s = NULL;
	opt->map->path_w = NULL;
	opt->map->path_e = NULL;
	opt->map->floor = -1;
	opt->map->sky = -1;
	opt->map->viewpos = 0;
	opt->map->flag = 0;
	opt->map->width = 0;
	opt->keys = -1;
	opt->old_keys = -1;
}

void	ft_init_images(t_opt *opt)
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
	opt->pic->wall_e = NULL;
	opt->pic->wall_s = NULL;
	opt->pic->wall_w = NULL;
	opt->pic->wall_n = NULL;
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
	opt->plr = malloc(sizeof(t_player));
	if (!opt->plr)
		puterror("can't allocate memory(plr)");
	opt->cnst = malloc(sizeof(t_cnst));
	if (!opt->cnst)
		puterror("can't allocate memory(constants)");
	ft_init_opt_map(opt);
}

void	ft_calculate_consts(t_opt *opt)
{
	opt->cnst->tan_plane = tan(FOV * M_PI / 360);
	opt->cnst->camX_const = 2.0 / (double)RES_X;
	opt->cnst->cos_rot = cos(ROT_SPEED);
	opt->cnst->angle = ((double)FOV / 180.0) * M_PI;
	opt->cnst->half_angle = opt->cnst->angle * 0.5;
	opt->cnst->map_step = opt->cnst->angle / REYS;
	opt->cnst->map_diff = (double)MAP_SIZE * 0.25;
	opt->cnst->b_p_p_del = opt->mand->b_p_p / 8;
}