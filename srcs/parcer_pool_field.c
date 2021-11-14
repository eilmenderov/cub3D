/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_pool_field.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:50:04 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 11:50:05 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

void	direction_init(t_vector *dir, char c, t_opt *opt)
{
	if (c == 'N' || c == 'S')
	{
		opt->plr->angle = 3 * M_PI / 2;
		if (c == 'S')
			dir->y = 1;
		else
			dir->y = -1;
		if (c == 'S')
			opt->plr->angle = M_PI / 2;
	}
	else
		dir->y = 0;
	if (c == 'E' || c == 'W')
	{
		opt->plr->angle = M_PI;
		if (c == 'E')
			dir->x = 1;
		else
			dir->x = -1;
		if (c == 'E')
			opt->plr->angle = 0;
	}
	else
		dir->x = 0;
}

void	ft_read_map(t_map *map, char *line, t_list **lst)
{
	int	len;

	len = ft_strlen_m(line, 0);
	if (line[0] && line[len - 1] == '1' && map->flag == 6)
		map->flag++;
	else if (map->flag == 6)
		return (free(line));
	if ((map->flag == 8 && line[0]))
		puterror("incorrect map field");
	if (len > map->width)
		map->width = len;
	if (line[0])
		ft_lstadd_back(lst, ft_lstnew(line));
	else
		free(line);
}

void	ft_pool_field(t_list *lst, int lst_size, t_map *map)
{
	t_list	*tmp;
	int		i;

	map->canvas = malloc(sizeof(char *) * (lst_size + 1));
	if (!map->canvas)
		puterror("can't allocate memory(canvas)");
	tmp = lst;
	i = 0;
	while (tmp)
	{
		map->canvas[i] = tmp->content;
		tmp->content = NULL;
		if (ft_ch_for_coinc(map->canvas[i][(int)map->opt->plr->pos.x], HERO))
			map->opt->plr->pos.y = i + 0.01;
		tmp = tmp->next;
		i++;
	}
	map->canvas[i] = NULL;
}
