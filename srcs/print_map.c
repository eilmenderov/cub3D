#include "head_cub.h"

void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->addr + (y * opt->line_length + x * (opt->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	sizepixel_player(t_opt *opt, int x, int y, int color)
{
	int	x_size;
	int	y_size;

	y_size = y - PIC_SIZE + 45;
	while (y_size < y && y_size < RES_Y)
	{
		x_size = x - PIC_SIZE + 45;
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
	int	step_x;
	int	step_y;

	y = 0;
	x = 0;
	step_x = PIC_SIZE;
	step_y = PIC_SIZE;
	while (opt->map->canvas[y])
	{
		x = 0;
		step_x = PIC_SIZE;
		while (opt->map->canvas[y][x])
		{
			if (opt->map->canvas[y][x] == '1')
				sizepixel(opt, step_x, step_y, 0xFFFFFF);
			else if (opt->map->canvas[y][x] == '0' || opt->map->canvas[y][x] == 'N')
			{
				sizepixel(opt, step_x, step_y, 0x708090);
				if (opt->map->canvas[y][x] == 'N' && opt->x_widht == -1 && opt->y_heidht == -1)
				{
					opt->x_widht = step_x;
					opt->y_heidht = step_y;
					printf("x = %d\ty = %d\n", opt->x_widht, opt->y_heidht);
					// sizepixel(opt, step_x, step_y, 0xFF0000);
					opt->map->canvas[y][x] = '0';
				}
			}

			x++;
			step_x += PIC_SIZE;
		}
		step_y += PIC_SIZE;
		y++;
	}
	sizepixel_player(opt, opt->x_widht, opt->y_heidht, 0xFF0000);
}
