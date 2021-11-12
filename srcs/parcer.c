/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:35:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/07 15:50:51 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

void	ft_pool_sprite_path(char **adress, char *line, t_map *map)
{
	int	i;
	int	len;

	if (*adress)
		puterror("duplicate map sprite");
	if (ft_count_words(line, ' ') != 2)
		puterror("incorrect side path format");
	map->flag += 1;
	i = ft_skip_fw(line, ' ');
	len = ft_strlen_m(&line[i], 0);
	if (len < 4 || ft_strncmp(&line[i] + len - 4, ".xpm", 5))
		puterror("incorrect sprite name, need <sprite_path.x>");
	*adress = ft_strdup(&line[i]);
}

void	ft_pool_collor(long *adress, char *line, t_map *map)
{
	int	i;
	int	rgb[3];

	if (*adress != -1)
		puterror("duplicate map color");
	i = ft_skip_fw(line, ' ');
	rgb[0] = ft_atoi_m(&line[i]);
	i = i + ft_strlen_m(&line[i], ',') + 1;
	rgb[1] = ft_atoi_m(&line[i]);
	i = i + ft_strlen_m(&line[i], ',') + 1;
	rgb[2] = ft_atoi_m(&line[i]);
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		puterror("incorrect color format");
	map->flag++;
	*adress = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	ft_check_line(t_map *map, char *line)
{
	char	*str;

	str = ft_first_word(line, ' ');
	if (!str && line)
		free (line);
	if (!str)
		return ;
	if (!ft_strcmp(str, "NO"))
		ft_pool_sprite_path(&map->path_n, line, map);
	else if (!ft_strcmp(str, "SO"))
		ft_pool_sprite_path(&map->path_s, line, map);
	else if (!ft_strcmp(str, "WE"))
		ft_pool_sprite_path(&map->path_w, line, map);
	else if (!ft_strcmp(str, "EA"))
		ft_pool_sprite_path(&map->path_e, line, map);
	else if (!ft_strcmp(str, "F"))
		ft_pool_collor(&map->floor, line, map);
	else if (!ft_strcmp(str, "C"))
		ft_pool_collor(&map->sky, line, map);
	else
		puterror("invalid string on map");
	free (str);
	free (line);
}

void	ft_read_map(t_map *map, char *line, t_list **lst)
{
	int	len;

	len = ft_strlen_m(line, 0);
	if (line[0] && line[len - 1] == '1' && map->flag == 6)
		map->flag++;
	else if (map->flag == 6)
		return (free(line));
	if ((map->flag == 8 && line[0]))
		puterror("incorrect map field");
	if (len > map->width)
		map->width = len;
	if (line[0])
		ft_lstadd_back(lst, ft_lstnew(line));
	else
		free(line);
}

void	ft_pool_field(t_list *lst, int lst_size, t_map *map)
{
	t_list	*tmp;
	int		i;

	map->canvas = malloc(sizeof(char *) * (lst_size + 1));
	if (!map->canvas)
		puterror("can't allocate memory(canvas)");
	tmp = lst;
	i = 0;
	while (tmp)
	{
		map->canvas[i] = tmp->content;
		tmp->content = NULL;
		if (ft_ch_for_coinc(map->canvas[i][(int)map->opt->plr->pos.x], HERO))
			map->opt->plr->pos.y = i;
		tmp = tmp->next;
		i++;
	}
	map->canvas[i] = NULL;
}

void	direction_init(t_vector *dir, char c, t_opt *opt)
{
	if (c == 'N' || c == 'S')
	{
		opt->plr->angle = 3 * M_PI / 2;
		if (c == 'S')
			dir->y = 1;
		else
			dir->y = -1;
		if (c == 'S')
			opt->plr->angle = M_PI / 2;
	}
	else
		dir->y = 0;
	if (c == 'E' || c == 'W')
	{
		opt->plr->angle = M_PI;
		if (c == 'E')
			dir->x = 1;
		else
			dir->x = -1;
		if (c == 'E')
			opt->plr->angle = 0;
	}
	else
		dir->x = 0;
}

void	ft_check_str(t_opt *opt, char *line)
{
	int	i;

	if (!line || opt->map->flag != 7)
		return ;
	if (!line[0])
		opt->map->flag++;
	i = -1;
	while (line[++i])
	{
		if (!ft_ch_for_coinc(line[i], SYMBOLS))
			puterror("incorrect symbols on the map");
		if (opt->map->viewpos && ft_ch_for_coinc(line[i], HERO))
			puterror("more then one hero on the map");
		else if (!opt->map->viewpos && ft_ch_for_coinc(line[i], HERO))
		{
			opt->map->viewpos = line[i];
			opt->plr->pos.x = i;
			direction_init(&opt->plr->dir, line[i], opt);
		}
	}
}

void	ft_check_map(t_opt *opt, int fd, int gnl)
{
	char	*line;
	t_list	*lst;

	lst = NULL;
	line = NULL;
	while (gnl)
	{
		gnl = ft_gnl_old(fd, &line);
		if (gnl < 0)
			puterror("get_next_line error");
		if (opt->map->flag < 6)
			ft_check_line(opt->map, line);
		else
		{
			ft_check_str(opt, line);
			ft_read_map(opt->map, line, &lst);
		}
	}
	opt->map->heigh = ft_lstsize(lst);
	ft_pool_field(lst, opt->map->heigh, opt->map);
	ft_free_all_lst(lst);
	close (fd);
}

void	ft_plane(t_player *player)
{
	player->plane.x = -player->dir.y * player->opt->cnst->tan_plane;
	player->plane.y = player->dir.x * player->opt->cnst->tan_plane;
}

void	ft_check_field(char **field, t_map *map)
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
			if (ft_ch_for_coinc(field[i][j], "NSEW0"))
			{
				if (!i || !field[i + 1] || !field[i][j + 1] || i == map->heigh)
					puterror("incorrect map field");
			}
			j++;
		}
		i++;
	}
}

void	ft_load_xmp(t_opt *opt, t_img *texture, char *file)
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
}

void	ft_init_sprites(t_opt *opt, t_map *map)
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

	len = ft_strlen_m(file, 0);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 5))
		puterror("incorrect map name, need <map_name.cub>");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		puterror("file does not exist, access denied or open error");
	ft_init_structs(opt);
	ft_check_map(opt, fd, 1);
	ft_check_field(opt->map->canvas, opt->map);
	ft_init_images(opt);
	ft_init_sprites(opt, opt->map);
	opt->map->canvas[(int)opt->plr->pos.y][(int)opt->plr->pos.x] = '0';
	ft_calculate_consts(opt);
	ft_plane(opt->plr);
}
