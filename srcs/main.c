/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/07 14:47:14 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

int	ft_check_p(t_map *map, t_opt *opt)
{
	(void)map;
	(void)opt;
	return (0);
}

int	keyhook(int key, t_opt *opt)
{
	int	step;

	step = (int)MAP_SIZE * MOVE_SPEED;
	if (key == W_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht += (step * sin(opt->angle));
		opt->x_widht += (step * cos(opt->angle));
	}
	if (key == A_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht -= (step * sin(opt->angle + M_PI_2));
		opt->x_widht -= (step * cos(opt->angle + M_PI_2));
	}
	if (key == S_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht -= (step * sin(opt->angle));
		opt->x_widht -= (step * cos(opt->angle));
	}
	if (key == D_KEY && !ft_check_p(opt->map, opt))
	{
		opt->y_heidht += (step * sin(opt->angle + M_PI_2));
		opt->x_widht += (step * cos(opt->angle + M_PI_2));
	}
	if (key == RL_KEY)
		opt->angle -= M_PI / ROT_SPEED;
	if (key == RR_KEY)
		opt->angle += M_PI / ROT_SPEED;
	if (key == 53)
		exit(0);
	return (key);
}

/* Добавить free */
int	closer(void)
{
	exit(0);
}

void	mand_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->mand->addr + (y * opt->mand->line_length + x
			* (opt->mand->b_p_p / 8));
	*(unsigned int *)dst = color;
}

void	print_mandatori(t_opt *opt)
{
	int	x;
	int	y;

	y = 0;
	while (y < RES_Y)
	{
		x = 0;
		while (x < RES_X)
		{
			if (y > RES_Y * 0.5)
				mand_pixel_put(opt, x, y, opt->map->floor);
			else
				mand_pixel_put(opt, x, y, opt->map->sky);
			x++;
		}
		y++;
	}
}

void	draw_line(t_opt *opt, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		// printf("start: %d end: %d\n", drawStart, drawEnd);
		my_mlx_pixel_put(opt, x, drawStart, color);
		drawStart++;
	}
}

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	lodev(t_opt *opt)
{
	// double posX = (double)opt->x_widht, posY = (double)opt->y_heidht;
	double posX = 22, posY = 12;
	double	dirX = sin(opt->angle);
	double	dirY = cos(opt->angle);
	// double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	double	w = screenWidth;
	double	h = screenHeight;
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
		//perform DDA
		// printf("stepX: %d	stepY: %d	deltaDistX: %f	deltaDistY: %f	sideDistX: %f	sideDistY: %f\n",
		// 		stepX, stepY, deltaDistX, deltaDistY, sideDistX, sideDistY), exit(0);
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
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0)
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

int	draw_all(t_opt *opt)
{
	print_mandatori(opt);
	lodev(opt);
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
	opt.x_widht = -1;
	opt.y_heidht = -1;
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_hook(opt.win, 2, 1L << 0, keyhook, &opt);
	mlx_loop_hook(opt.mlx, draw_all, &opt);
	mlx_loop(opt.mlx);
}
