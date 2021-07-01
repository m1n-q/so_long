/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:35:14 by mishin            #+#    #+#             */
/*   Updated: 2021/07/01 14:39:24 by shin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "mlx.h"
# include "keys.h"
# include "type.h"

# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define BLOCK 64
# define BG 0x00C2F3DD

# define FIN_MSG "DONE! PRESS ANY KEY TO QUIT."
# define NOT_FIN_MSG "YOU HAVE TO EAT ALL RAMEN!"

# define ERR_ARG "usage: ./so_long [file ...]\n"
# define ERR_INPUT "not a valid map\nThe map must be composed of \
only 5 possible characters:\n0 -> empty space\n1 -> wall\nC -> collectible\n\
E -> map exit\nP -> player’s starting position\n"
# define ERR_RECT "map is not rectangular\n"
# define ERR_MALLOC "malloc error\n"
# define ERR_PLAYER "map must have a player: P\n"
# define ERR_ELEMS "map must have at least one exit, one collectible, and one player\n"
# define ERR_WALLS "map must be surrounded by walls\n"
# define ERR_MLX "failed to initialize mlx\n"
# define ERR_WIN "failed to create window\n"
# define ERR_IMG "failed to create images\n"

#define ALL_COLLECTED 1
#define NOT_COLLECTED -1
#define MOVED 1
#define NOT_MOVED 0
													# include <stdio.h>

/* linked list */

t_ll	*ll_new(char c);
void	ll_push(t_ll **ll, t_ll *new);
int		ll_clear(t_ll **ll);

/* input */

int		input_to_ll(int fd, t_ll **ll);	//TODO: EXCEPTION (DOUBLE P o E) CHECK
int		check_rectangular(t_ll *ll, t_map *map);
int		ll_to_map(t_ll *ll, t_map *map);
int		get_elems_count(t_map *map);

/* map */

void	init_map(t_map *map);
int		clear_map(t_map *map);
int		check_surrounding(t_map	*map);
int		get_pos_player(t_map *map);



/* img */

int		make_bg_img(t_param_set *set, int color);
int		make_elems_img(t_param_set *set);
void	put_bg_img(t_param_set *set);
int		put_elems_img(t_param_set *set, int is_collected);
void	clear_elems_img(t_param_set *set);

/* move */

int		move_player(int	keycode, t_param_set *set);

/* window */

int		leave_window(t_param_set *set);
int		notifying(t_param_set *set, int is_collected);

/* err */
void	myerr(char *msg);
void	check_ll_err(int fd, t_ll **head, t_param_set *set);
void	check_map_err(t_param_set *set);
void	check_mlx_err(t_param_set *set);
void	check_img_err(t_param_set *set);
#endif
