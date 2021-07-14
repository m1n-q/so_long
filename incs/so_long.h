/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:35:14 by mishin            #+#    #+#             */
/*   Updated: 2021/07/14 23:09:10 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "../mlx/mlx.h"
# include "keys.h"
# include "type.h"

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

# define BLOCK 64
# define BG 0x00C2F3DD

# define ERR_ARG "usage: ./so_long [file ...]\n"
# define ERR_RECT "map is not rectangular\n"
# define ERR_MALLOC "malloc error\n"
# define ERR_PLAYER "map must have a player: P\n"
# define ERR_WALLS "map must be surrounded by walls\n"
# define ERR_MLX "failed to initialize mlx\n"
# define ERR_WIN "failed to create window\n"
# define ERR_IMG "failed to create images\n"
# define ERR_INPUT "invalid map\nmap must be composed of ( 0, 1, C, P, E )\n"
# define ERR_ELEMS "map must have 1 exit, 1 player, at least 1 collectible\n"

/*
** status after move
*/

# define EXIT_OK 1
# define EXIT_FAIL -1
# define MOVED 1
# define NOT_MOVED 0

/*
** linked list
*/
t_ll	*ll_new(char c);
void	ll_push(t_ll **head, t_ll *new);
int		ll_clear(t_ll **head);

/*
** input
*/
int		input_to_ll(int fd, t_ll **head);
int		check_rectangular(t_ll **head, t_map *map);
int		ll_to_map(t_ll **head, t_map *map);
int		get_elems_count(t_map *map);

/*
** map
*/
void	init_map(t_map *map);
int		clear_map(t_map *map);
int		check_surrounding(t_map	*map);
int		get_pos_player(t_map *map);

/*
** img
*/
int		make_bg_img(t_param_set *set, int color);
int		make_elems_img(t_param_set *set);
void	put_bg_img(t_param_set *set, t_vector *v);
int		put_elems_img(t_param_set *set, int is_collected);
void	clear_elems_img(t_param_set *set);

/*
** move
*/
int		move_player(int	keycode, t_param_set *set);

/*
** err
*/
void	errmsg(char *msg);
void	check_ll_err(int fd, t_ll **head, t_param_set *set);
void	check_map_err(t_param_set *set);
void	check_mlx_err(t_param_set *set);
void	check_img_err(t_param_set *set);

/*
** tools
*/
int		leave_window(t_param_set *set);
void	print_movement_count(int count);
#endif
