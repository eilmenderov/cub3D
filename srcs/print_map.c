#include "head_cub.h"

void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->addr + (y * opt->line_length + x * (opt->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
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
