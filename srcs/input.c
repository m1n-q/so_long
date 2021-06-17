/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:33:56 by mishin            #+#    #+#             */
/*   Updated: 2021/06/17 21:03:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		input_to_ll(int fd, t_ll **ll)	
{
	t_ll	*new;
	ssize_t	size;
	char	c;

	while ((size = read(fd, &c, 1)) > 0)
	{	
		if (c == '1' || \
			c == '0' || \
			c == 'P' || \
			c == 'C' || \
			c == 'E' || \
			c == '\n')
		{
			new = ll_new(c);
			if (!new)
				return (ll_clear(ll));
			ll_push(ll, new);
		}
		else
			return (ll_clear(ll));
	}
	return (size);
}

int		check_rectangular(t_ll *ll, t_map *map)
{
	t_ll	*cur;
	int		x;

	x = 0;
	cur = ll;
	while (cur)
	{
		if (cur->c != '\n')
		{
			if (map->height == 0)
				map->width++;
			else
				x++;
		}
		else
		{
			map->height++;
			if (map->height != 1 && x != map->width)
				return (ll_clear(&ll));
			x = 0;
		}
		cur = cur->next;
	}
	return (0);
}

int		ll_to_map(t_ll *ll, t_map *map)		//NORM
{
	t_ll	*cur;
	int 	i;
	int		j;

	cur = ll;
	map->map = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->map)
		return (ll_clear(&ll));
	i = -1;
	while (++i < map->height)
	{
		(map->map)[i] = (char *)ft_calloc(map->width + 1, sizeof(char));
		if (!((map->map)[i]))
		{
			while (--i >= 0)
				free((map->map)[i]);
			return (ll_clear(&ll));
		}
		j = -1;
		while (++j < map->width)
		{
			if (cur->c == '\n')
				cur = cur->next;
			(map->map)[i][j] = cur->c;
			cur = cur->next;
		}
	}
	ll_clear(&ll);
	return (0);
}
