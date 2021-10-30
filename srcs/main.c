/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/10/30 10:49:53 by fcarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

void	puterror(char *errorline)
{
	ft_putendl_fd(errorline, 1);
	exit(0);
}

void	parse_map(t_opt *opt)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = *opt->map;
	opt->canvas = malloc(sizeof(char *) * ft_lstsize(lst));
	if (!opt->canvas)
		exit (0);
	while (lst)
	{
		opt->canvas[i] = lst->content;
		lst = lst->next;
		i++;
	}
	opt->canvas[i] = NULL;
}

void	read_map(t_opt *opt, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	ft_gnl_old(fd, &line);
	*(opt->map) = ft_lstnew(line);
	while (ft_gnl_old(fd, &line))
		ft_lstadd_back(opt->map, ft_lstnew(line));
	ft_lstadd_back(opt->map, ft_lstnew(line));
	parse_map(opt);
}

int	keyhook(int key, t_opt *opt)
{
	if (key == 53)
		exit(0);
	(void)opt;
	return (key);
}

void	fillopt(t_opt *opt)
{
	opt->x_widht = 64;
	opt->y_heidht = 64;
	opt->path_wall = "wall1.XPM";
}

int	main(int argc, char **argv)
{
	t_opt	opt;

	fillopt(&opt);
	if (argc != 2)
		puterror("Map error");
	opt.map = malloc(sizeof(t_list *));
	read_map(&opt, argv[1]);
	opt.mlx = mlx_init();
	opt.img_wall = mlx_xpm_file_to_image(opt.mlx, opt.path_wall, &opt.x_widht, &opt.y_heidht);
	opt.win = mlx_new_window(opt.mlx, 1920, 1080, "cub3d");
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img_wall, 0, 0);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img_wall, 64, 0);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img_wall, 128, 0);
	mlx_key_hook(opt.win, keyhook, &opt);
	mlx_loop(opt.mlx);
}
