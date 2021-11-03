#include "head_cub.h"

void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->addr + (y * opt->line_length + x * (opt->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_cast_one_ray(t_opt *opt, int diff)
{
	float	x;
	float	y;
	float	l;
	float	full_angle;

	full_angle = opt->angle * 0.5;
	x = opt->x_widht - diff / 2;
	y = opt->y_heidht - diff / 2;
	while (opt->map->canvas[(int)(y / PIC_SIZE)][(int)(x / PIC_SIZE)] != '1')
	{
		x += cos(full_angle);
		y += sin(full_angle);
		my_mlx_pixel_put(opt, (int)x, (int)y, 0x990099);
	}
	l = sqrt(pow(opt->x_widht - x, 2) + pow(opt->y_heidht - y, 2));
	printf("ray_len: %f\n", l);
}

void	ft_draw_3d(t_opt *opt, float len, float start, float x)
{
	float	y;
	float	end;

	end = start + len;
	y = 0;
	while (y < RES_Y)
	{
		if (y >= start && y <= end)
			my_mlx_pixel_put(opt, (int)x, (int)y, COLOR_DEEP);
		else
			my_mlx_pixel_put(opt, (int)x, (int)y, 0);
		y += 1;
	}
}

void	ft_cast_rays(t_opt *opt, int diff)
{
	float	x;
	float	y;
	float	start;
	float	end;

	float	l;
	float	h_stl;
	float	h_y0;

	if (opt->angle < 0)
		opt->angle = M_PI * 2;
	start = opt->angle;
	end = start + ANGLE;
	// mlx_clear_window(opt->mlx,  opt->win);
	while (start < end)
	{
		x = opt->x_widht - diff / 2;
		y = opt->y_heidht - diff / 2;
		while (opt->map->canvas[(int)(y / PIC_SIZE)][(int)(x / PIC_SIZE)] != '1')
		{
			x += cos(start);
			y += sin(start);
			my_mlx_pixel_put(opt, (int)x, (int)y, 0x990099);
		}
		l = sqrt(pow(opt->x_widht - x, 2) + pow(opt->y_heidht - y, 2));
		h_stl = opt->map->h_stl / l;
		h_y0 = (RES_Y / 2.0) - (h_stl / 2);
		// printf("vysota: %f	y0: %f\n", h_stl, h_y0);
		ft_draw_3d(opt, h_stl, h_y0, x);
		start += (ANGLE / REYS);
	}
}

void	sizepixel_player(t_opt *opt, int x, int y, int color)
{
	int	x_size;
	int	y_size;
	int	diff;

	diff = PIC_SIZE - (int)(PIC_SIZE * 0.2);
	// ft_cast_one_ray(opt, diff);
	(void)color;
	ft_cast_rays(opt, diff);
	y_size = y - diff;
	while (y_size < y && y_size < RES_Y)
	{
		x_size = x - diff;
		while (x_size < x && x_size < RES_X)
		{
			my_mlx_pixel_put(opt, x_size, y_size, color);
			x_size++;
		}
		y_size++;
	}
}

void	sizepixel(t_opt *opt, int x, int y, int color)
{
	int	x_size;
	int	y_size;

	y_size = y;
	while (y_size < y + PIC_SIZE && y_size < RES_Y)
	{
		x_size = x;
		while (x_size < x + PIC_SIZE && x_size < RES_X)
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
	int	step_x;
	int	step_y;

	y = -1;
	step_y = 0;
	while (opt->map->canvas[++y])
	{
		step_x = 0;
		x = -1;
		while (opt->map->canvas[y][++x])
		{
			if (opt->map->canvas[y][x] == '1')
				sizepixel(opt, step_x, step_y, 0xFFFFFF);
			else if (ft_ch_for_coinc(opt->map->canvas[y][x], "0NSEW"))
			{
				sizepixel(opt, step_x, step_y, 0x708090);
				if (ft_ch_for_coinc(opt->map->canvas[y][x], HERO))
				{
					opt->x_widht = step_x;
					opt->y_heidht = step_y;
					opt->map->viewpos = opt->map->canvas[y][x];
					opt->map->canvas[y][x] = '0';
				}
			}
			step_x += PIC_SIZE;
		}
		step_y += PIC_SIZE;
	}
	sizepixel_player(opt, (int)opt->x_widht, (int)opt->y_heidht, 0xFF0000);
}
