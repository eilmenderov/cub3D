#include "head_cub.h"

void	draw_line(t_opt *opt, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(opt, x, drawStart, color);
		drawStart++;
	}
}

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

t_vector	get_tex_data(t_vector ray, t_player *plr, t_opt *opt, char *tex)
{
	t_vector	trash;
	double		dist;
	char		side;

	dist = ft_find_dist(ray, plr, opt->map->canvas, &side);
	// printf("dist: %f\n", dist);
	if (side == 'V')
	{
		trash.x = plr->pos.x + dist * ray.x;
		if (ray.y > 0)
			*tex = 'N';
		else
			*tex = 'S';
	}
	else if (side == 'H')
	{
		trash.x = plr->pos.y + dist * ray.y;
		if (ray.x > 0)
			*tex = 'W';
		else
			*tex = 'E';
	}
	trash.x -= floor(trash.x);
	trash.y = dist;
	// printf("v_x: %f	v_y: %f\n", trash.x, trash.y);
	return (trash);
}

unsigned int *ft_get_pix(t_img *img, int x, int y)
{
	return ((unsigned *)(img->addr + y * img->line_length
		+ x * (img->b_p_p / 8)));
}

void	put_tex_stripe(t_opt *opt, int x, t_vector trash, char tex)
{
	int		p_x;
	int		p_y;
	int		start;
	int		finish;
	int		color;
	double	step;
	double	pos;

	step = (double)SPRITE_SIZE / trash.y;
	start = (RES_Y - (int)trash.y) / 2;
	// printf("start: %d y: %f	   step: %f\n", start, trash.y, step);
	if (start < 0)
		start = 0;
	finish = RES_Y - start;
	p_x = (int)((double)SPRITE_SIZE * trash.x);
	pos = (start + ((int)trash.y - RES_Y) / 2) * step;
	color = COLOR_RED;
	if (tex == 'N')
		color = COLOR_TEXT;
	else if (tex == 'S')
		color = MENU_BACKGROUND;
	else if (tex == 'W')
		color = COLOR_DEEP;
	// (void)opt;
	// (void)x;
	// (void)tex;
	// printf("%f\n", trash.y);
	// printf("start: %d	finish %d	pos: %f	step: %f\n", start, finish, pos, step);
	while (start < finish)
	{
		p_y = (int)pos & (SPRITE_SIZE - 1);
		// *ft_get_pix(opt->mand->img, x, start) = *ft_get_pix(tex, p_x, p_y);
		my_mlx_pixel_put(opt, x, start, color);
		pos += step;
		start++;
	}
}

void	ft_draw_walls(t_opt *opt)
{
	int			x;
	double		cameraX;
	char		tex;
	t_vector	ray;
	t_vector	trash;

	x = 0;
	// printf("pls_x: %f plr_y: %f\n", opt->plr->pos_x, opt->plr->pos_y), exit (0);
	while (x < RES_X)
	{
		cameraX = 2 * (double)x / (double)RES_X - 1;
		ray.x = opt->plr->dir.x + opt->plr->plane.x * cameraX;
		ray.y = opt->plr->dir.y + opt->plr->plane.y * cameraX;
		trash = get_tex_data(ray, opt->plr, opt, &tex);
		// printf("tes: %p\n", tex);
		// printf("bef - x: %f	y: %f\n", trash.x, trash.y);
		trash.y = (double)RES_Y / trash.y;
		// printf("aft - x: %f	y: %f\n", trash.x, trash.y);
		put_tex_stripe(opt, x, trash, tex);
		// if (x > 5)
		// 	exit(0);
		x++;
	}
}

void	lodev(t_opt *opt)
{
	double posX = (double)opt->plr->pos.x, posY = (double)opt->plr->pos.y;
	// printf("x: %f	y: %f\n",  posX, posY); exit(0);
	// double posX = 22, posY = 12;
	double	dirX = cos(opt->plr->angle * 0.5);
	double	dirY = sin(opt->plr->angle * 0.5);
	// double dirX = -1, dirY = 0;
	double planeX = 0, planeY = ANGLE * 0.5;
	double	w = RES_X;
	double	h = RES_Y;
	int x;

	x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / w - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;
		
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : ft_abs_f(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : ft_abs_f(1 / rayDirY);

		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform dist
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// printf("mapX: %d	mapY: %d\n", mapX, mapY);
			// printf("stepX: %d	stepY: %d	deltaDistX: %f	deltaDistY: %f	sideDistX: %f	sideDistY: %f\n",
			// 	stepX, stepY, deltaDistX, deltaDistY, sideDistX, sideDistY);
			//Check if ray has hit a wall
			// if(worldMap[mapX][mapY] > 0)
			// 	hit = 1;
			if(opt->map->canvas[mapX][mapY] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		
		//Calculate height of line to draw on screen
		// printf("perpWallDist: %f\n", perpWallDist), exit(0);
		int lineHeight = (int)(h / perpWallDist);
		// printf("lineHeight: %d\n", lineHeight), exit(0);
		
		//calculate lowest and higest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)
			drawEnd = h - 1;
		
		//choose wall color
		int	color = COLOR_RED;
		//give x and y sides different brightness
		if (side == 1)
			color = color / 2;
		draw_line(opt, x, drawStart, drawEnd, color);
		x++;
	}
}