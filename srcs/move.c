#include "head_cub.h"

int	ft_check_p(t_map *map, t_opt *opt, double x, double y)
{
	x = opt->plr->pos.x + x;
	y = opt->plr->pos.y + y;
	if (map->canvas[(int)y][(int)x] != '1')
		return (0);
	return (1);
}

void	rotate_player(t_opt *opt, double rot_speed)
{
	double	sin_al;
	double	cos_al;
	double	length;

	sin_al = sin(rot_speed);
	cos_al = opt->cnst->cos_rot;
	opt->plr->dir.x = opt->plr->dir.x * cos_al - opt->plr->dir.y * sin_al;
	opt->plr->dir.y = opt->plr->dir.x * sin_al + opt->plr->dir.y * cos_al;
	length = hypot(opt->plr->dir.x, opt->plr->dir.y);
	opt->plr->dir.x = opt->plr->dir.x / length;
	opt->plr->dir.y = opt->plr->dir.y / length;
	ft_plane(opt->plr);
	opt->plr->angle += rot_speed;
}

void	move(t_opt *opt, double step_x, double step_y)
{
	if(!ft_check_p(opt->map, opt, step_x, 0))
		opt->plr->pos.x += step_x;
	if(!ft_check_p(opt->map, opt, 0, step_y))
		opt->plr->pos.y += step_y;
}
 
void	move_player(t_opt *opt)
{
	double	step_x;
	double	step_y;

	step_x = opt->plr->dir.x * MOVE_SPEED;
	step_y = opt->plr->dir.y * MOVE_SPEED;
	if (opt->keys->w == 1)
		move(opt, step_x, step_y);
	if (opt->keys->s == 1)
		move(opt, -step_x, -step_y);
	if (opt->keys->d == 1)
		move(opt, -step_y, step_x);
	if (opt->keys->a == 1)
		move(opt, step_y, -step_x);
	if (opt->keys->arrow_l == 1)
		rotate_player(opt, -ROT_SPEED);
	if (opt->keys->arrow_r == 1)
		rotate_player(opt, ROT_SPEED);
}
