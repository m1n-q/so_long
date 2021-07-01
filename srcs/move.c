/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:34:26 by mishin            #+#    #+#             */
/*   Updated: 2021/07/01 18:19:54 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	move_up(t_param_set *set)
{
	if (set->map.pos.y >= 1 && \
		(set->map.map)[set->map.pos.y - 1][set->map.pos.x] != '1')
	{
		(set->map.map)[set->map.pos.y][set->map.pos.x] = '0';
		set->map.pos.y -= 1;
		if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'C')
			set->map.collectibles--;
		else if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'E')
		{
			if (!set->map.collectibles)
			{
				set->map.fin = 1;
				return (ALL_COLLECTED);
			}
			else
			{	
				set->map.pos.y += 1;
				(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
				return (NOT_COLLECTED);
			}
		}
		(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
		return (MOVED);
	}
	return (NOT_MOVED);
}

static int	move_down(t_param_set *set)
{
	if (set->map.pos.y + 1 < set->map.height && \
		(set->map.map)[set->map.pos.y + 1][set->map.pos.x] != '1')
	{
		(set->map.map)[set->map.pos.y][set->map.pos.x] = '0';
		set->map.pos.y += 1;
		if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'C')
			set->map.collectibles--;
		else if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'E')
		{
			if (!set->map.collectibles)
			{
				set->map.fin = 1;
				return (ALL_COLLECTED);
			}
			else
			{
				set->map.pos.y -= 1;
				(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
				return (NOT_COLLECTED);
			}
		}
		(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
		return (MOVED);
	}
	return (NOT_MOVED);
}

static int	move_left(t_param_set *set)
{
	if (set->map.pos.x >= 1 && \
		(set->map.map)[set->map.pos.y][set->map.pos.x - 1] != '1')
	{
		(set->map.map)[set->map.pos.y][set->map.pos.x] = '0';
		set->map.pos.x -= 1;
		if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'C')
			set->map.collectibles--;
		else if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'E')
		{
			if (!set->map.collectibles)
			{
				set->map.fin = 1;
				return (ALL_COLLECTED);
			}
			else
			{
				set->map.pos.x += 1;
				(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
				return (NOT_COLLECTED);
			}
		}
		(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
		return (MOVED);
	}
	return (NOT_MOVED);
}

static int	move_right(t_param_set *set)
{
	if (set->map.pos.y + 1 < set->map.width && \
		(set->map.map)[set->map.pos.y][set->map.pos.x + 1] != '1')
	{
		(set->map.map)[set->map.pos.y][set->map.pos.x] = '0';
		set->map.pos.x += 1;
		if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'C')
			set->map.collectibles--;
		else if ((set->map.map)[set->map.pos.y][set->map.pos.x] == 'E')
		{
			if (!set->map.collectibles)
			{
				set->map.fin = 1;
				return (ALL_COLLECTED);
			}
			else
			{
				set->map.pos.x -= 1;
				(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
				return (NOT_COLLECTED);
			}
		}
		(set->map.map)[set->map.pos.y][set->map.pos.x] = 'P';
		return (MOVED);
	}
	return (NOT_MOVED);
}

int			move_player(int	keycode, t_param_set *set)
{
	static int	count;
	int			moved;

	moved = 0;
	if (set->map.fin || keycode == KEY_ESC)
		return (leave_window(set));
	if (keycode == KEY_W)
		if ((moved = move_up(set)) == NOT_COLLECTED)
			return (put_elems_img(set, NOT_COLLECTED));
	if (keycode == KEY_S)
		if ((moved = move_down(set)) == NOT_COLLECTED)
			return (put_elems_img(set, NOT_COLLECTED));
	if (keycode == KEY_A)
		if ((moved = move_left(set)) == NOT_COLLECTED)
			return (put_elems_img(set, NOT_COLLECTED));
	if (keycode == KEY_D)
		if ((moved = move_right(set)) == NOT_COLLECTED)
			return (put_elems_img(set, NOT_COLLECTED));
	set->map.fin ? put_elems_img(set, ALL_COLLECTED) : put_elems_img(set, 0);
	if (moved)
		print_movement_count(++count);
	return (0);
}
