/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:34:40 by mishin            #+#    #+#             */
/*   Updated: 2021/07/01 18:40:43 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		leave_window(t_param_set *set)
{
	clear_elems_img(set);
	clear_map(&set->map);
	mlx_destroy_image(set->ptr.mlx, set->bg.data.img);
	mlx_destroy_window(set->ptr.mlx, set->ptr.win);
	exit(0);
	return (0);
}

void	print_movement_count(int count)
{
	ft_putstr_fd("# movements ==> ", 1);
	ft_putnbr_fd(count, 1);
	ft_putchar_fd('\n', 1);
}
