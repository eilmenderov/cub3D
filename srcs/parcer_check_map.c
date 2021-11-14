/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_check_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:50:01 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 11:50:01 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

static void	ft_pool_sprite_path(char **adress, char *line, t_map *map)
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
		puterror("incorrect sprite name, need <sprite_path.xpm>");
	*adress = ft_strdup(&line[i]);
}

static void	ft_pool_collor(long *adress, char *line, t_map *map)
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

static void	ft_check_line(t_map *map, char *line)
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

static void	ft_check_str(t_opt *opt, char *line)
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
			opt->plr->pos.x = i + 0.01;
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
	if (!opt->map->viewpos)
		puterror("hero not found");
}
