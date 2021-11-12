/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_cub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:09:06 by vleida            #+#    #+#             */
/*   Updated: 2021/11/07 16:30:09 by vleida           ###   ########.fr       */
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
# define ANGLE			1.4835
# define FOV			85.0
# define DELIM			10
# define ROT_SPEED		0.06
# define MOVE_SPEED		0.1

/* keys */
# define W_KEY			13
# define A_KEY			0
# define S_KEY			1
# define D_KEY			2
# define RL_KEY			123
# define RR_KEY			124
# define ESC_KEY		53

/* field_symbols */
# define NONE		'0'
# define WALL		'1'
# define HERO		"NSEW"
# define SYMBOLS	"NSEW 01"

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		b_p_p;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_pic
{
	t_img			*wall_n;
	t_img			*wall_s;
	t_img			*wall_w;
	t_img			*wall_e;

	struct s_opt	*opt;
}				t_pic;

typedef struct s_map
{
	int				heigh;
	int				width;

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

typedef struct s_player
{
	t_vector		plane;
	t_vector		pos;
	t_vector		dir;
	double			angle;
	int				move;
	int				strafe;
	int				rotate;
	int				run;
	struct s_opt	*opt;
}				t_player;

typedef struct s_dist
{
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		x;
	int		y;
}				t_dist;

typedef struct s_cnst
{
	double	tan_plane;
	double	camX_const;
	double	cos_rot;
	double	half_angle;
	double	map_step;
	double	map_diff;
	double	half_diff;
	double	angle;
	int		b_p_p_del;
}				t_cnst;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		arrow_l;
	int		arrow_r;
}				t_keys;

typedef struct s_opt
{
	void			*mlx;
	void			*win;

	t_keys			*keys;
	t_cnst			*cnst;
	t_img			*mand;
	t_map			*map;
	t_player		*plr;
	t_pic			*pic;
}				t_opt;



/* 6/5 main.c */
void	print_mandatori(t_opt *opt);
void	puterror(char *errorline);

/* 3/5 parcer.c */
void	ft_parcer(t_opt *opt, char *file);
void	ft_plane(t_player *player);

/* 1/5 dev_utils.c */
void	ft_printf_all_info(t_opt *opt);

/* 1/5 utils.c */
void	puterror(char *errorline);
double	ft_angle(t_player *plr);
int		ft_atoi_m(const char *str);

/* 5/5 print_map.c */
void	print_minimap(t_opt *opt);
void	sizepixel(t_opt *opt, int x, int y, int color);
void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color);
void	sizepixel_player(t_opt *opt, int x, int y, int color);

/* 3/5 init.c */
void	ft_init_images(t_opt *opt);
void	ft_init_structs(t_opt *opt);
void	ft_calculate_consts(t_opt *opt);

/* 3/5 loudev.c */
void	draw_line(t_opt *opt, int x, int drawStart, int drawEnd, int color);
void	ft_draw_walls(t_opt *opt);

/* 3/5	move.c */
void	move_player(t_opt *opt);

#endif