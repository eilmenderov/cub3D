/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_cub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:09:06 by vleida            #+#    #+#             */
/*   Updated: 2021/11/01 15:46:20 by fcarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HEAD_CUB_H
# define HEAD_CUB_H

# include "../libft/libft.h"
# include "../minilibx_opengl/mlx.h"

# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

# define PIC_SIZE	50
# define RES_X		1920
# define RES_Y		1080

/* field_symbols */
# define NONE		'0'
# define WALL		'1'
# define HERO		"NSEW"
# define SYMBOLS	"NSEW 01"

typedef struct s_pic
{
	void			*img_wall;
	struct s_opt	*opt;
}				t_pic;

typedef struct s_map
{
	unsigned char	flag;
	char			**canvas;
	char			*path_n;
	char			*path_s;
	char			*path_w;
	char			*path_e;
	char			viewpos;
	unsigned int	floor;
	unsigned int	sky;
	struct s_opt	*opt;
}				t_map;

typedef struct s_opt
{
	t_list	**lst;

	int		x_widht;
	int		y_heidht;

	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	t_map	*map;
	t_pic	*pic;
}				t_opt;

/* 6/5 main.c */
void	puterror(char *errorline);

/* 3/5 parcer.c */
void	ft_parcer(t_opt *opt, char *file);

/* 1/5 dev_utils.c */
void	ft_printf_all_info(t_opt *opt);

/* 1/5 utils.c */
void	puterror(char *errorline);
void	printmap(t_opt *opt);
void	sizepixel(t_opt *opt, int x, int y, int color);
void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color);
void	sizepixel_player(t_opt *opt, int x, int y, int color);

#endif