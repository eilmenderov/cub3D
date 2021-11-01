/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:26:25 by vleida            #+#    #+#             */
/*   Updated: 2021/11/01 13:07:23 by fcarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

void	ft_printf_all_info(t_opt *opt)
{
	int	i;

	printf("=============== map ===============\n");
	printf("map_field:\n");
	i = -1;
	while (opt->map->canvas[++i])
		printf("%s\n", opt->map->canvas[i]);
	printf("N_sprite: %s\n", opt->map->path_n);
	printf("S_sprite: %s\n", opt->map->path_s);
	printf("W_sprite: %s\n", opt->map->path_w);
	printf("E_sprite: %s\n", opt->map->path_e);
	printf("viewpos: |%c|\n", opt->map->viewpos);
	printf("Flor_col: %d\n", opt->map->floor);
	printf("Sky_coll: %d\n", opt->map->sky);
	printf("=============== end ===============\n");
}
