/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:34:40 by mishin            #+#    #+#             */
/*   Updated: 2021/06/29 01:09:01 by shin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		notifying(t_param_set *set, int is_collected)
{
	put_elems_img(set, is_collected);
	return (-1);
}

int		leave_window(t_param_set *set)
{
	clear_elems_img(set);
	clear_map(&set->map);
	mlx_destroy_image(set->ptr.mlx, set->bg.data.img);
	mlx_destroy_window(set->ptr.mlx, set->ptr.win);
	exit(0);
	return (0);
}
