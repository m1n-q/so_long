/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:34:09 by mishin            #+#    #+#             */
/*   Updated: 2021/07/14 21:44:34 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int			fd;
	t_ll		*ll;
	t_param_set	set;

	ll = NULL;
	init_map(&set.map);
	if (argc != 2)
		errmsg(ERR_ARG);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		perror("Error\nso_long");
		exit(errno);
	}
	check_ll_err(fd, &ll, &set);
	check_map_err(&set);
	check_mlx_err(&set);
	check_img_err(&set);
	put_elems_img(&set, 0);
	mlx_hook(set.ptr.win, KEY_PRESS, 0L, move_player, &set);
	mlx_hook(set.ptr.win, DESTROY_NOTIFY, 0L, leave_window, &set);
	mlx_loop(set.ptr.mlx);
}
