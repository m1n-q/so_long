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
			{
				ll_clear(&ll);
				return (-1);
			}
			x = 0;
		}
		cur = cur->next;
	}
	return (0);
}

int		ll_to_map(t_ll *ll, t_map *map)
{
	t_ll	*cur;
	int 	i;
	int		j;

	cur = ll;
	map->map = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->map)
	{	
		ll_clear(&ll);
		return (-1);
	}
	i = 0;
	while (i < map->height)
	{
		(map->map)[i] = (char *)ft_calloc(map->width + 1, sizeof(char));
		if (!((map->map)[i]))
		{
			ll_clear(&ll);
			while (i--)
				free((map->map)[i]);
			return (-1);
		}
		j = 0;
		while (j < map->width)
		{
			if (cur->c == '\n')
				cur = cur->next;
			(map->map)[i][j] = cur->c;
			j++;
			cur = cur->next;
		}
		i++;
	}
	ll_clear(&ll);
	return (0);
}
