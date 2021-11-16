/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loudev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:49:47 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 11:49:47 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

static double	ft_find_dist(t_vector ray, t_player *plr,
		char **map, char *side)
{
	t_dist	dist;
	int		fl;

	ft_init_dist(&dist, ray, plr);
	while (map[dist.y][dist.x] != '1')
	{
		if (dist.sidedistx < dist.sidedisty)
		{
			dist.sidedistx += dist.deltadistx;
			dist.x += dist.stepx;
			fl = 1;
		}
		else
		{
			dist.sidedisty += dist.deltadisty;
			dist.y += dist.stepy;
			fl = 0;
		}
	}
	if (fl)
		*side = 'H';
	if (fl)
		return ((dist.x - plr->pos.x + (1 - dist.stepx) * 0.5) / ray.x);
	*side = 'V';
	return ((dist.y - plr->pos.y + (1 - dist.stepy) * 0.5) / ray.y);
}

static t_vector	get_tex_data(t_vector ray, t_player *plr,
		t_opt *opt, t_img **tex)
{
	t_vector	trash;
	double		dist;
	char		side;

	dist = ft_find_dist(ray, plr, opt->map->canvas, &side);
	if (side == 'V')
	{
		trash.x = plr->pos.x + dist * ray.x;
		if (ray.y > 0)
			*tex = opt->pic->wall_n;
		else
			*tex = opt->pic->wall_s;
	}
	else if (side == 'H')
	{
		trash.x = plr->pos.y + dist * ray.y;
		if (ray.x > 0)
			*tex = opt->pic->wall_w;
		else
			*tex = opt->pic->wall_e;
	}
	trash.x -= floor(trash.x);
	trash.y = dist;
	return (trash);
}

static unsigned int	*ft_get_color(t_img *img, int x, int y)
{
	return ((unsigned *)(img->addr + y * img->line_length
		+ x * img->b_p_p));
}

static void	put_tex_stripe(t_opt *opt, int x, t_vector trash, t_img *tex)
{
	int			p_x;
	int			p_y;
	int			start;
	int			finish;
	t_vector	step_pos;

	step_pos.x = (double)SPRITE_SIZE / trash.y;
	start = (RES_Y - (int)trash.y) / 2;
	if (start < 0)
		start = 0;
	finish = RES_Y - start;
	p_x = (int)((double)SPRITE_SIZE * trash.x);
	step_pos.y = (start + ((int)trash.y - RES_Y) * 0.5) * step_pos.x;
	while (start < finish)
	{
		p_y = (int)step_pos.y & (SPRITE_SIZE - 1);
		my_mlx_pixel_put(opt, x, start, *ft_get_color(tex, p_x, p_y));
		step_pos.y += step_pos.x;
		start++;
	}
}

void	ft_draw_walls(t_opt *opt)
{
	int			x;
	double		camerax;
	t_img		*tex;
	t_vector	ray;
	t_vector	trash;

	x = 0;
	while (x < RES_X)
	{
		camerax = (double)x * opt->cnst->camx_const - 1;
		ray.x = opt->plr->dir.x + opt->plr->plane.x * camerax;
		ray.y = opt->plr->dir.y + opt->plr->plane.y * camerax;
		trash = get_tex_data(ray, opt->plr, opt, &tex);
		trash.y = (double)RES_Y / trash.y;
		put_tex_stripe(opt, x, trash, tex);
		x++;
	}
}
