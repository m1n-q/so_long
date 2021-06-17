/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:34:09 by mishin            #+#    #+#             */
/*   Updated: 2021/06/17 20:34:10 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int			fd;
	t_ll		*ll;
	t_param_set set;
	
	ll = NULL;
	init_map(&set.map);
	if (argc != 2)
		myerr(ERR_ARG);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		err();
	if (input_to_ll(fd, &ll) == -1)	
		myerr(ERR_INPUT);
	if (check_rectangular(ll, &set.map) == -1)
		myerr(ERR_RECT);
	if (ll_to_map(ll, &set.map) == -1)	
		myerr(ERR_MALLOC);
	if (get_pos_player(&set.map) == -1)
		myerr(ERR_PLAYER);
	if (get_elems_count(&set.map) == -1)
		myerr(ERR_ELEMS);
	if (check_surrounding(&set.map) == -1)
		myerr(ERR_WALLS);
	if ((set.ptr.mlx = mlx_init()) == NULL)
		myerr(ERR_MLX); // free map!
	if ((set.ptr.win = mlx_new_window(set.ptr.mlx, set.map.width * BLOCK, set.map.height * BLOCK, "MAP")) == NULL)
		myerr(ERR_WIN);
	if (make_elems_img(&set) == -1 || make_bg_img(&set, BG) == -1)
		myerr(ERR_IMG);
	put_elems_img(&set);
	mlx_hook(set.ptr.win, KeyPress, KeyPressMask, move_player, &set);
	mlx_hook(set.ptr.win, DestroyNotify, KeyPressMask, leave_window, &set);
	mlx_loop(set.ptr.mlx);
}

// 잘 했는지 테스트 하고 하나로 묶기
// NOT_COL & ALL_COL msg 어떻게 할지?
