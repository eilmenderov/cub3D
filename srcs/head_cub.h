/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_cub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:09:06 by vleida            #+#    #+#             */
/*   Updated: 2021/11/05 18:58:24 by fcarl            ###   ########.fr       */
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
# define MAP_SIZE		10
# define PIC_SIZE		30
# define SPRITE_SIZE	64
# define DELTA			0
# define RES_X			1280
# define RES_Y			720
# define REYS			100
# define ANGLE			1.57
# define DELIM			10
# define ROT_SPEED		45
# define MOVE_SPEED		0.15

/* color */
# define COLOR_TEXT			0xEAEAEA
# define BACKGROUND			0x222222
# define MENU_BACKGROUND	0x1E1E1E
# define COLOR_UP			0xEF8633
# define COLOR_RED			0xCC3333
# define COLOR_ZERO			0x33FF00
# define COLOR_WHITE		0xFFFFCC
# define COLOR_DEEP			0x00CCFF
# define COLOR_GOLD			0x705335
# define COLOR_GREEN		0x004B49

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
	float			h_stl;

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		b_p_p;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_opt
{
	float	x_widht;
	float	y_heidht;
	float	angle;

	void	*mlx;
	void	*win;

	t_img	*mand;
	t_img	*minimap;
	t_map	*map;
	t_pic	*pic;
}				t_opt;

/* 6/5 main.c */
void	print_mandatori(t_opt *opt);
void	puterror(char *errorline);

/* 3/5 parcer.c */
void	ft_parcer(t_opt *opt, char *file);

/* 1/5 dev_utils.c */
void	ft_printf_all_info(t_opt *opt);

/* 1/5 utils.c */
void	puterror(char *errorline);
float	ft_angle(float alpha);

void	print_minimap(t_opt *opt);
void	sizepixel(t_opt *opt, int x, int y, int color);
void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color);
void	sizepixel_player(t_opt *opt, int x, int y, int color);

/* 2/5 init.c*/
void	ft_init_structs(t_opt *opt);

#endif