/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:35:26 by vleida            #+#    #+#             */
/*   Updated: 2021/10/31 15:01:47 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

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
	opt->pic->opt = opt;
	opt->map->opt = opt;
	opt->x_widht = PIC_SIZE;
	opt->y_heidht = PIC_SIZE;
}

void	parse_map(t_opt *opt) // временно на переделку
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = *opt->lst;
	opt->map->canvas = malloc(sizeof(char *) * ft_lstsize(lst));
	if (!opt->map->canvas)
		exit(0);
	while (lst)
	{
		opt->map->canvas[i] = lst->content;
		lst = lst->next;
		i++;
	}
	opt->map->canvas[i] = NULL;
}

void	read_map(t_opt *opt, char *filename) // временно на переделку
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	ft_gnl_old(fd, &line);
	*(opt->lst) = ft_lstnew(line);
	while (ft_gnl_old(fd, &line))
		ft_lstadd_back(opt->lst, ft_lstnew(line));
	ft_lstadd_back(opt->lst, ft_lstnew(line));
	parse_map(opt);
}

// void	ft_check_map(t_opt *opt, int fd, int gnl)
// {
// 	char	*line;

// 	line = NULL;
// 	while (gnl)
// 	{
// 		gnl = ft_gnl_old(fd, &line);
// 		if (gnl < 0)
// 			puterror("get_next_line error");
// 	}
// }

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
	close(fd); // dhtvtyyj
	ft_init_structs(opt);
	// ft_check_map(opt, fd, 1);
	opt->lst = malloc(sizeof(t_list *));
	read_map(opt, file);
	ft_printf_all_info(opt);
}
