/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:34:40 by mishin            #+#    #+#             */
/*   Updated: 2021/06/17 21:12:03 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		notifying(t_param_set *set, char *msg)
{
	if (set->map.fin)
		mlx_clear_window(set->ptr.mlx, set->ptr.win);
	mlx_string_put(set->ptr.mlx, set->ptr.win, \
	set->map.width * BLOCK / 2, set->map.height * BLOCK /2 , 0x00FF0000, msg);
	return (-1);
	//TODO : make image instead string put!
}

int		leave_window(t_param_set *set)
{
	clear_elems_img(set);
	clear_map(&set->map);
	mlx_destroy_image(set->ptr.mlx, set->bg.data.img);
	mlx_destroy_window(set->ptr.mlx, set->ptr.win);
	return (1);
}

