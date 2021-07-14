/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:33:44 by mishin            #+#    #+#             */
/*   Updated: 2021/07/14 14:42:05 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_mlx_err(t_param_set *set)
{
	if ((set->ptr.mlx = mlx_init()) == NULL)
		errmsg(ERR_MLX);
	if ((set->ptr.win = mlx_new_window(\
						set->ptr.mlx, \
						set->map.width * BLOCK, \
						set->map.height * BLOCK, \
						"MAP")) == NULL)
	{
		clear_map(&set->map);
		errmsg(ERR_WIN);
	}
}

void	check_ll_err(int fd, t_ll **head, t_param_set *set)
{
	if (input_to_ll(fd, head) == -1)
		errmsg(ERR_INPUT);
	if (check_rectangular(head, &set->map) == -1)
		errmsg(ERR_RECT);
	if (ll_to_map(head, &set->map) == -1)
		errmsg(ERR_MALLOC);
}

void	check_map_err(t_param_set *set)
{
	if (get_pos_player(&set->map) == -1)
		errmsg(ERR_PLAYER);
	if (get_elems_count(&set->map) == -1)
		errmsg(ERR_ELEMS);
	if (check_surrounding(&set->map) == -1)
		errmsg(ERR_WALLS);
}

void	check_img_err(t_param_set *set)
{
	if (make_elems_img(set) == -1 || make_bg_img(set, BG) == -1)
		errmsg(ERR_IMG);
}

void	errmsg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(errno);
}
