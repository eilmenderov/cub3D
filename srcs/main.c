/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarl <fcarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:14:26 by vleida            #+#    #+#             */
/*   Updated: 2021/11/01 12:40:57 by fcarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

int	keyhook(int key, t_opt *opt)
{
	if (key == 53)
		exit(0);
	(void)opt;
	return (key);
}

int	closer(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_opt	opt;

	if (argc != 2)
		puterror("incorrect arguments, need only one");
	ft_parcer(&opt, argv[1]);
	printmap(&opt);
	mlx_put_image_to_window(opt.mlx, opt.win, opt.img, 20, 20);
	mlx_hook(opt.win, 17, 0l, closer, &opt);
	mlx_key_hook(opt.win, keyhook, &opt);
	mlx_loop(opt.mlx);
}
