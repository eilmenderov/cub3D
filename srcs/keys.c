/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:49:43 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 13:20:15 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

int	key_press(int key, t_opt *opt)
{
	if (key == W_KEY)
		opt->keys->w = 1;
	else if (key == S_KEY)
		opt->keys->s = 1;
	else if (key == D_KEY)
		opt->keys->d = 1;
	else if (key == A_KEY)
		opt->keys->a = 1;
	else if (key == RL_KEY)
		opt->keys->arrow_l = 1;
	else if (key == RR_KEY)
		opt->keys->arrow_r = 1;
	if (key == ESC_KEY)
		closer(opt);
	return (key);
}

int	key_release(int key, t_opt *opt)
{
	if (key == W_KEY)
		opt->keys->w = -1;
	else if (key == S_KEY)
		opt->keys->s = -1;
	else if (key == D_KEY)
		opt->keys->d = -1;
	else if (key == A_KEY)
		opt->keys->a = -1;
	else if (key == RL_KEY)
		opt->keys->arrow_l = -1;
	else if (key == RR_KEY)
		opt->keys->arrow_r = -1;
	return (key);
}
