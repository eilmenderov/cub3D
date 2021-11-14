/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:35:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 14:06:05 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

static int	ft_check_char(char **field, int i, int j, t_map *map)
{
	int	len;

	if (!ft_ch_for_coinc(field[i][j + 1], CHECK) || (!j && field[i][j] != '1'))
		return (1);
	if (j && !ft_ch_for_coinc(field[i][j - 1], CHECK))
		return (1);
	if (!i && i == map->heigh - 1)
		return (0);
	if (field[i][j] != '1' && ((int)ft_strlen_m(field[i + 1], 0) < j
		|| (int)ft_strlen_m(field[i - 1], 0) < j))
		return (1);
	len = ft_strlen_m(field[i + 1], 0);
	if (!ft_ch_for_coinc(field[i + 1][j], CHECK))
		return (1);
	if (len >= j && field[i][j] == '0' && (!ft_ch_for_coinc(field[i + 1]
		[j + 1], CHECK) || !ft_ch_for_coinc(field[i + 1][j - 1], CHECK)))
		return (1);
	len = ft_strlen_m(field[i - 1], 0);
	if (!ft_ch_for_coinc(field[i - 1][j], CHECK))
		return (1);
	if (len >= j && field[i][j] == '0' && (!ft_ch_for_coinc(field[i - 1]
		[j + 1], CHECK) || !ft_ch_for_coinc(field[i - 1][j - 1], CHECK)))
		return (1);
	return (0);
}

static void	ft_check_field(char **field, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (field[i])
	{
		j = 0;
		if ((int)ft_strlen_m(field[i], 0) == ft_how_many_char(field[i], ' '))
			puterror("incorrect map field(spaces)");
		while (field[i][j])
		{
			if (ft_ch_for_coinc(field[i][j], "0"))
			{
				if (((!i || i == map->heigh - 1) && field[i][j] == '0')
					|| ft_check_char(field, i, j, map))
					puterror("incorrect map field(walls)");
			}
			j++;
		}
		i++;
	}
}

static void	ft_load_xmp(t_opt *opt, t_img *texture, char *file)
{
	int	fl[2];

	if (!texture)
		puterror("can't allocate memory(texture)");
	texture->img = mlx_xpm_file_to_image(opt->mlx, file, &fl[0], &fl[1]);
	if (!texture->img)
		puterror(ft_strjoin("can not read xpm file ", file));
	if (fl[0] != SPRITE_SIZE || fl[0] != fl[1])
		puterror(ft_strjoin("incorrect xpm size ", file));
	texture->addr = mlx_get_data_addr(texture->img, &texture->b_p_p,
			&texture->line_length, &texture->endian);
	texture->b_p_p = texture->b_p_p / 8;
}

static void	ft_init_sprites(t_opt *opt, t_map *map)
{
	opt->pic->wall_e = malloc(sizeof(t_img));
	ft_load_xmp(opt, opt->pic->wall_e, map->path_e);
	opt->pic->wall_s = malloc(sizeof(t_img));
	ft_load_xmp(opt, opt->pic->wall_s, map->path_s);
	opt->pic->wall_n = malloc(sizeof(t_img));
	ft_load_xmp(opt, opt->pic->wall_n, map->path_n);
	opt->pic->wall_w = malloc(sizeof(t_img));
	ft_load_xmp(opt, opt->pic->wall_w, map->path_w);
}

void	ft_parcer(t_opt *opt, char *file)
{
	int	fd;
	int	len;
	int	max_width;
	int	max_height;

	len = ft_strlen_m(file, 0);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 5))
		puterror("incorrect map name, need <map_name.cub>");
	mlx_get_screen_size(&max_width, &max_height);
	if (max_width < RES_X || max_height < RES_Y)
		puterror("incorrect resolution");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		puterror("file does not exist, access denied or open error");
	ft_init_structs(opt);
	ft_check_map(opt, fd, 1);
	opt->map->canvas[(int)opt->plr->pos.y][(int)opt->plr->pos.x] = '0';
	ft_check_field(opt->map->canvas, opt->map);
	ft_init_images(opt);
	ft_init_sprites(opt, opt->map);
	ft_calculate_consts(opt);
	ft_plane(opt->plr);
}
