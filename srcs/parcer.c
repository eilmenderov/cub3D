/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:35:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/01 18:45:41 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

int	ft_atoi_m(const char *str)
{
	int					negative;
	unsigned long long	res;

	negative = 1;
	res = 0;
	while (*str && (*str == 32 || (*str > 8 && *str < 14)))
		str++;
	if (*str == '-')
		puterror("incorrect color format(atoi_m 1)");
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9' && res <= FT_ATOI_MN)
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	if ((res > FT_ATOI_MV && negative == 1) || (*str != ',' && *str != 0))
		puterror("incorrect color format(atoi_m 2)");
	return ((int)res * negative);
}

void	ft_init_opt_map(t_opt *opt)
{
	opt->pic->opt = opt;
	opt->map->opt = opt;
	opt->x_widht = PIC_SIZE;
	opt->y_heidht = PIC_SIZE;
	opt->map->canvas = NULL;
	opt->map->path_n = NULL;
	opt->map->path_s = NULL;
	opt->map->path_w = NULL;
	opt->map->path_e = NULL;
	opt->map->floor = -1;
	opt->map->sky = -1;
	opt->map->viewpos = 0;
	opt->map->flag = 0;
}

void	ft_init_structs(t_opt *opt)
{
	opt->map = malloc(sizeof(t_map));
	if (!opt->map)
		puterror("can't allocate memory(map)");
	opt->pic = malloc(sizeof(t_pic));
	if (!opt->pic)
		puterror("can't allocate memory(pic)");
	opt->mlx = mlx_init();
	if (!opt->mlx)
		puterror("can't initialize mlx");
	opt->win = mlx_new_window(opt->mlx, RES_X, RES_Y, "cub3d");
	if (!opt->win)
		puterror("can't create game window");
	opt->img = mlx_new_image(opt->mlx, RES_X, RES_Y);
	if (!opt->img)
		puterror("can't create new image");
	opt->addr = mlx_get_data_addr(opt->img, &opt->bits_per_pixel,
			&opt->line_length, &opt->endian);
	if (!opt->addr)
		puterror("can't get addr");
	ft_init_opt_map(opt);
}

void	ft_pool_sprite_path(char **adress, char *line, t_map *map)
{
	int	i;

	if (*adress)
		puterror("duplicate map sprite");
	if (ft_count_words(line, ' ') != 2)
		puterror("incorrect side path format");
	map->flag += 1;
	i = ft_skip_fw(line, ' ');
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
	printf("r = %d	g = %d	b = %d\n", rgb[0], rgb[1], rgb[2]);
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
	if (line[0] && line[ft_strlen_m(line, 0) - 1] == '1' && map->flag == 6)
		map->flag++;
	else if (map->flag == 6)
		return (free(line));
	if (line[0] && line[ft_strlen_m(line, 0) - 1] == '1')
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
		tmp = tmp->next;
		i++;
	}
	map->canvas[i] = NULL;
}

void	ft_check_map(t_opt *opt, int fd, int gnl)
{
	char	*line;
	t_list	*lst;
	int		lst_size;

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
			ft_read_map(opt->map, line, &lst);
	}
	lst_size = ft_lstsize(lst);
	ft_pool_field(lst, lst_size, opt->map);
	ft_free_all_lst(lst);
	close (fd);
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
	ft_printf_all_info(opt);
}
