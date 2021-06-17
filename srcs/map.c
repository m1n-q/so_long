#include "so_long.h"


void	init_map(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->walls = 0;
	map->pos = (t_vector){.x = 0, .y = 0};
	map->fin = 0;
}

int		clear_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
		free(map->map[i++]);
	free(map->map);
	return (-1);
}



int		get_pos_player(t_map *map)
{
	
	int			i;
	int			j;

	i = 0;
	while ((map->map)[i])
	{
		j = 0;
		while ((map->map)[i][j])
		{
			if ((map->map)[i][j] == 'P')
			{	
				map->pos = (t_vector){.y = i, .x = j};
				return (0);
			}
			j++;
		}
		i++;	
	}
	clear_map(map);
	return (-1);
}


int		get_elems_count(t_map *map)
{
	int i;
	int j;
    int	p;
    int	e;

    p = 0;
    e = 0;
	i = 0;
	while ((map->map)[i])
	{
		j = 0;
		while ((map->map)[i][j])
		{
			if ((map->map)[i][j] == 'C')
				map->collectibles++;
			else if ((map->map)[i][j] == '1')
				map->walls++;
            else if ((map->map)[i][j] == 'P')
				p++;
            else if ((map->map)[i][j] == 'E')
				e++;
			j++;
		}
		i++;	
	}
	if (map->collectibles && map->walls && p == 1 && e == 1)
		return (0);
	else
	{
		clear_map(map);
		return (-1);
	}
}

int		check_surrounding(t_map	*map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->map[0][i] != '1')
			return (clear_map(map));
		if (map->map[map->height - 1][i] != '1')
			return (clear_map(map));
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0] != '1')
			return (clear_map(map));
		if (map->map[i][map->width - 1] != '1')
			return (clear_map(map));
		i++;
	}
	return (0);
}
