#include "head_cub.h"

void	ft_init_dist(t_dist *dist, t_vector ray, t_player *plr)
{
	dist->deltaDistX = fabs(1 / ray.x);
	dist->deltaDistY = fabs(1 / ray.y);
	dist->x = (int)plr->pos.x;
	dist->y = (int)plr->pos.y;
	if (ray.x > 0)
	{
		dist->stepX = 1;
		dist->sideDistX = (ceil(plr->pos.x) - plr->pos.x) * dist->deltaDistX;
	}
	else
	{
		dist->stepX = -1;
		dist->sideDistX = (plr->pos.x - floor(plr->pos.x)) * dist->deltaDistX;
	}
	if (ray.y > 0)
	{
		dist->stepY = 1;
		dist->sideDistY = (ceil(plr->pos.y) - plr->pos.y) * dist->deltaDistY;
	}
	else
	{
		dist->stepY = -1;
		dist->sideDistY = (plr->pos.y - floor(plr->pos.y)) * dist->deltaDistY;
	}
}

double	ft_find_dist(t_vector ray, t_player *plr, char **map,char *side)
{
	t_dist	dist;
	int		fl;

	ft_init_dist(&dist, ray, plr);
	while(map[dist.y][dist.x] != '1')
	{
		if (dist.sideDistX < dist.sideDistY)
		{
			dist.sideDistX += dist.deltaDistX;
			dist.x += dist.stepX;
			fl = 1;
		}
		else
		{
			dist.sideDistY += dist.deltaDistY;
			dist.y += dist.stepY;
			fl = 0;
		}
	}
	if (fl)
		*side = 'H';
	if (fl)
		return ((dist.x - plr->pos.x + (1 - dist.stepX) / 2) / ray.x);
	*side = 'V';
	return ((dist.y - plr->pos.y + (1 - dist.stepY) / 2) / ray.y);
}

t_vector	get_tex_data(t_vector ray, t_player *plr, t_opt *opt, t_img **tex)
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

unsigned int *ft_get_pix(t_img *img, int x, int y)
{
	return ((unsigned *)(img->addr + y * img->line_length
		+ x * (img->b_p_p / 8)));
}

void	put_tex_stripe(t_opt *opt, int x, t_vector trash, t_img *tex)
{
	int		p_x;
	int		p_y;
	int		start;
	int		finish;
	double	step;
	double	pos;

	step = (double)SPRITE_SIZE / trash.y;
	start = (RES_Y - (int)trash.y) / 2;
	if (start < 0)
		start = 0;
	finish = RES_Y - start;
	p_x = (int)((double)SPRITE_SIZE * trash.x);
	pos = (start + ((int)trash.y - RES_Y) / 2) * step;
	while (start < finish)
	{
		p_y = (int)pos & (SPRITE_SIZE - 1);
		my_mlx_pixel_put(opt, x, start, *ft_get_pix(tex, p_x, p_y));
		pos += step;
		start++;
	}
}

void	ft_draw_walls(t_opt *opt)
{
	int			x;
	double		cameraX;
	t_img		*tex;
	t_vector	ray;
	t_vector	trash;

	x = 0;
	while (x < RES_X)
	{
		cameraX = (double)x * opt->cnst->camX_const - 1;
		ray.x = opt->plr->dir.x + opt->plr->plane.x * cameraX;
		ray.y = opt->plr->dir.y + opt->plr->plane.y * cameraX;
		trash = get_tex_data(ray, opt->plr, opt, &tex);
		trash.y = (double)RES_Y / trash.y;
		put_tex_stripe(opt, x, trash, tex);
		x++;
	}
}
