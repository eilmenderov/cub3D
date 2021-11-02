/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_cub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:09:06 by vleida            #+#    #+#             */
/*   Updated: 2021/11/02 17:14:29 by fcarl            ###   ########.fr       */
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

/* pic */
# define PIC_SIZE		30
# define SPRITE_SIZE	64
# define DELTA			5
# define RES_X			1280
# define RES_Y			720
# define REYS			200
# define ANGLE			1

/* keys */
# define W_KEY			13
# define A_KEY			0
# define S_KEY			1
# define D_KEY			2
# define RL_KEY			123
# define RR_KEY			124

/* field_symbols */
# define NONE		'0'
# define WALL		'1'
# define HERO		"NSEW"
# define SYMBOLS	"NSEW 01"

typedef struct s_pic
{
	void			*wall_n;
	void			*wall_s;
	void			*wall_w;
	void			*wall_e;

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
	long			floor;
	long			sky;
	struct s_opt	*opt;
}				t_map;

typedef struct s_opt
{
	float	x_widht;
	float	y_heidht;
	float	angle;

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