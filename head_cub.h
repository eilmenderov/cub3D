/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_cub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:09:06 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 14:07:05 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_CUB_H
# define HEAD_CUB_H

# include "./libft/libft.h"
# include "./minilibx_opengl/mlx.h"

# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

/* pic */
# define RES_X			1280
# define RES_Y			720
# define REYS			1000
# define FOV			85.0
# define ROT_SPEED		0.05
# define MOVE_SPEED		0.05
# define SPRITE_SIZE	64

/* minimap */
# define MAP_SIZE		5
# define MAP_W_COLOR	0xFFFFFF
# define MAP_PL_COLOR	0xFF0000
# define MAP_RAY_COLOR	0x990099

/* keys */
# define W_KEY			13
# define A_KEY			0
# define Q_KEY			12
# define E_KEY			14
# define S_KEY			1
# define D_KEY			2
# define RL_KEY			123
# define RR_KEY			124
# define ESC_KEY		53

/* field_symbols */
# define NONE		'0'
# define WALL		'1'
# define HERO		"NSEW"
# define CHECK		"01"
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
	struct s_opt	*opt;
}				t_player;

typedef struct s_dist
{
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	int		stepx;
	int		stepy;
	int		x;
	int		y;
}				t_dist;

typedef struct s_cnst
{
	double	tan_plane;
	double	camx_const;
	double	cos_rot;
	double	half_angle;
	double	map_step;
	double	map_diff;
	double	half_diff;
	double	angle;
	int		b_p_p_del;
	int		half_resy;
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

/* 5/5 init.c */
void	ft_init_structs(t_opt *opt);
void	ft_init_images(t_opt *opt);
void	ft_init_dist(t_dist *dist, t_vector ray, t_player *plr);
void	ft_calculate_consts(t_opt *opt);

/* 2/5 keys.c */
int		key_press(int key, t_opt *opt);
int		key_release(int key, t_opt *opt);

/* 5/5 loudev.c */
void	ft_draw_walls(t_opt *opt);

/* 5/5 main.c / main_bonus.c */
int		closer(t_opt *opt);
void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color);

/* 4/5	move.c */
void	move_player(t_opt *opt);

/* 5/5 parcer_check_map.c */
void	ft_check_map(t_opt *opt, int fd, int gnl);

/* 3/5 parcer_pool_field.c */
void	direction_init(t_vector *dir, char c, t_opt *opt);
void	ft_read_map(t_map *map, char *line, t_list **lst);
void	ft_pool_field(t_list *lst, int lst_size, t_map *map);

/* 5/5 parcer.c */
void	ft_parcer(t_opt *opt, char *file);

/* 5/5 print_map_bonus.c */
void	print_minimap(t_opt *opt);

/* 4/5 utils.c */
void	puterror(char *errorline);
void	ft_plane(t_player *player);
double	ft_angle(t_player *plr);
int		ft_atoi_m(const char *str);

#endif
