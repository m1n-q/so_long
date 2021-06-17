#include "libft.h"
#include "mlx.h"
#include "keys.h"
#include <fcntl.h>
#include <stdio.h>


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// addr 		-> img의 첫 픽셀 주소
// bpp			-> 한 픽셀당 비트
//		   		   ( / 8 : 한 픽셀당 바이트)
// line_length	-> 한 라인의 "바이트"
//				   ( 다음 라인으로 넘어가는 "바이트" )

typedef struct	s_ptr {
	void	*mlx;
	void	*win;
}				t_ptr;

typedef struct	s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct	s_map
{
	int			width;
	int			height;
	t_vector	pos;
	char		**map;
	int			collectibles;
}				t_map;

typedef struct	s_ll
{
	char	c;
	struct s_ll	*next;
}				t_ll;

typedef struct	s_map_and_func
{
	t_map	*map;
	t_ptr	*ptr;
	void (*func)();
}				t_map_and_func;



t_ll	*ll_new(char c)
{
	t_ll	*ret;

	ret = (t_ll *)malloc(sizeof(t_ll));
	if (!ret)
		return (NULL);
	ret->c = c;
	ret->next = NULL;
	return (ret);
}

void	ll_push(t_ll **ll, t_ll *new)
{
	t_ll	*cur;

	if (!ll)
		return ;
	if (!*ll)
	{
		*ll = new;
		return ;
	}
	cur = *ll;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	ll_clear(t_ll **ll)
{
	t_ll	*cur;
	t_ll	*tmp;

	if (!ll)
		return ;
	cur = *ll;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	*ll = NULL;
}

/*
The map must be composed of only 5 possible characters: 0 for an empty
space, 1 for a wall, C for a collectible, E for map exit and P for the player’s
starting position.
*/

void	map_to_img(t_map *map, t_ptr *ptr)
{
	int		i;
	int		j;
	t_data	img;
	char	*addr;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if ((map->map)[i][j] == '1')
			{
				img.img = mlx_new_image(ptr->mlx, 10, 10);
				addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
				for (int a = 0; a < 10; a++)
				{
					((unsigned int*)(addr))[a] = 0x00FF0000;
					for (int b = 0; b < 10; b++)
					{
						((unsigned int*)(addr))[a + b *(img.line_length / 4)] = 0x00FF0000;
					}
				}
				mlx_put_image_to_window(ptr->mlx, ptr->win, img.img, j * 10, i * 10 );
			}

			else if ((map->map)[i][j] == '0')
			{
				img.img = mlx_new_image(ptr->mlx, 10, 10);
				addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
				for (int a = 0; a < 10; a++)
				{
					((unsigned int*)(addr))[a] = 0x00000000;
					for (int b = 0; b < 10; b++)
					{
						((unsigned int*)(addr))[a + b *(img.line_length / 4)] = 0x00000000;
					}
				}
				mlx_put_image_to_window(ptr->mlx, ptr->win, img.img, j * 10, i * 10 );
			}

			else if ((map->map)[i][j] == 'P')
			{
				img.img = mlx_new_image(ptr->mlx, 10, 10);
				addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
				for (int a = 0; a < 10; a++)
				{
					((unsigned int*)(addr))[a] = 0x000000FF;
					for (int b = 0; b < 10; b++)
					{
						((unsigned int*)(addr))[a + b *(img.line_length / 4)] = 0x000000FF;
					}
				}
				mlx_put_image_to_window(ptr->mlx, ptr->win, img.img, j * 10, i * 10 );
			}

			else if ((map->map)[i][j] == 'E')
			{
				img.img = mlx_new_image(ptr->mlx, 10, 10);
				addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
				for (int a = 0; a < 10; a++)
				{
					((unsigned int*)(addr))[a] = 0x0000FF00;
					for (int b = 0; b < 10; b++)
					{
						((unsigned int*)(addr))[a + b *(img.line_length / 4)] = 0x0000FF00;
					}
				}
				mlx_put_image_to_window(ptr->mlx, ptr->win, img.img, j * 10, i * 10 );
			}

			else if ((map->map)[i][j] == 'C')
			{
				img.img = mlx_new_image(ptr->mlx, 10, 10);
				addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
				for (int a = 0; a < 10; a++)
				{
					((unsigned int*)(addr))[a] = 0x0000FFFF;
					for (int b = 0; b < 10; b++)
					{
						((unsigned int*)(addr))[a + b *(img.line_length / 4)] = 0x0000FFFF;
					}
				}
				mlx_put_image_to_window(ptr->mlx, ptr->win, img.img, j * 10, i * 10 );
			}
			j++;
		}
		i++;
	}
}

int		input_to_ll(int fd, t_ll **ll)	//TODO: EXCEPTION (DOUBLE P o E) CHECK
{
	t_ll	*new;
	ssize_t	size;
	char	c;
	int		p;
	int		e;

	p = 0;
	e = 0;
	size = 1;
	while ((size = read(fd, &c, 1)) > 0)
	{	
		if (c == '1' || \
			c == '0' || \
			c == 'P' || \
			c == 'C' || \
			c == 'E' || \
			c == '\n')
		{
			if (c == 'P')
			{	
				if (!p)
					p = 1;
				else
				{
					ll_clear(ll);
					return (-1);
				}
			}
			
			if (c == 'E')
			{	
				if (!e)
					e = 1;
				else
				{
					ll_clear(ll);
					return (-1);
				}
			}
			new = ll_new(c);
			ll_push(ll, new);
		}
		else
		{
			ll_clear(ll);
			return (-1);
		}
	}
	return (size);
}
void	init_map(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->pos = (t_vector){.x = 0, .y = 0};
}
int		check_ll(t_ll *ll, t_map *map)
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
		return (-1);
	i = 0;
	while (i < map->height)
	{
		(map->map)[i] = (char *)ft_calloc(map->width + 1, sizeof(char));
		if (!((map->map)[i]))
		{
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
	return (0);
	

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
	return (-1);
}

int		get_collectibles_count(t_map *map)
{
	
	int			i;
	int			j;

	i = 0;
	while ((map->map)[i])
	{
		j = 0;
		while ((map->map)[i][j])
		{
			if ((map->map)[i][j] == 'C')
				map->collectibles++;
			j++;
		}
		i++;	
	}
	return (map->collectibles ? 0 : -1);
}


void	print_map(char **map)
{
	int	i;
	int	j;

	printf("\n______________________\n");
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			ft_putchar_fd(map[i][j++], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}

	printf("\n______________________\n");
}

int	move_player(int	keycode, t_map *map)
{	
	if (keycode == KEY_W)
	{
		if (map->pos.y >= 1 && (map->map)[map->pos.y - 1][map->pos.x] != '1')
		{	
			(map->map)[map->pos.y][map->pos.x] = '0';
			map->pos.y -= 1;
			if ((map->map)[map->pos.y][map->pos.x] == 'C')
				map->collectibles--;
			else if((map->map)[map->pos.y][map->pos.x] == 'E')
			{
				if (!map->collectibles)
					printf("GOAL!\n");
				else
				{
					printf("YOU HAVE TO COLLECT ALL C!\n");
					map->pos.y += 1;
					(map->map)[map->pos.y][map->pos.x] = 'P';
				}
			}
			(map->map)[map->pos.y][map->pos.x] = 'P';
		}
	}
	
	if (keycode == KEY_S)
	{
		if (map->pos.y + 1 < map->height && (map->map)[map->pos.y + 1][map->pos.x] != '1')
		{
			(map->map)[map->pos.y][map->pos.x] = '0';
			map->pos.y += 1;
			if ((map->map)[map->pos.y][map->pos.x] == 'C')
				map->collectibles--;
			else if((map->map)[map->pos.y][map->pos.x] == 'E')
			{
				if (!map->collectibles)
					printf("GOAL!\n");
				else
				{
					printf("YOU HAVE TO COLLECT ALL C!s\n");
					map->pos.y -= 1;
					(map->map)[map->pos.y][map->pos.x] = 'P';
				}
			}
			(map->map)[map->pos.y][map->pos.x] = 'P';
		}
	}

	if (keycode == KEY_A)
	{
		if (map->pos.x >= 1 && (map->map)[map->pos.y][map->pos.x - 1] != '1')
		{
			(map->map)[map->pos.y][map->pos.x] = '0';
			map->pos.x -= 1;
			if ((map->map)[map->pos.y][map->pos.x] == 'C')
				map->collectibles--;
			else if((map->map)[map->pos.y][map->pos.x] == 'E')
			{
				if (!map->collectibles)
					printf("GOAL!\n");
				else
				{
					printf("YOU HAVE TO COLLECT ALL C!\n");
					map->pos.x += 1;
					(map->map)[map->pos.y][map->pos.x] = 'P';
				}
			}
			(map->map)[map->pos.y][map->pos.x] = 'P';
		}
	}

	if (keycode == KEY_D)
	{
		if (map->pos.y + 1 < map->width && (map->map)[map->pos.y][map->pos.x + 1] != '1')
		{
			(map->map)[map->pos.y][map->pos.x] = '0';
			map->pos.x += 1;
			if ((map->map)[map->pos.y][map->pos.x] == 'C')
				map->collectibles--;
			else if((map->map)[map->pos.y][map->pos.x] == 'E')
			{
				if (!map->collectibles)
					printf("GOAL!\n");
				else
				{
					printf("YOU HAVE TO COLLECT ALL C!\n");
					map->pos.x -= 1;
					(map->map)[map->pos.y][map->pos.x] = 'P';
				}
			}
			(map->map)[map->pos.y][map->pos.x] = 'P';
		}
	}
	// set->func(set->map, set->ptr);
	print_map(map->map);
	return (0);

}

void	print_ll(t_ll *ll)
{
	t_ll *cur;

	cur = ll;
	printf("head = %c\n", ll->c);
	while (cur)
	{
		// if ((cur->c) != '\n')
			printf("%hhd - ", cur->c);
		// else
		// 	printf("\\n - ");
		cur = cur->next;
	}
}


int	main(int argc, char **argv)
{

	t_ptr	ptr;
	int		fd;
	t_ll	*ll;
	t_map	map;
	t_map_and_func set;

	set.map = &map;
	set.ptr = &ptr;
	set.func = map_to_img;

	ll = NULL;
	init_map(&map);
	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, 1080, 720, "MAP");

	if (argc != 2)
		exit(1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit(2);
	if (input_to_ll(fd, &ll) == -1)
		exit(3);
	if (check_ll(ll, &map) == -1)
		exit(4);
	if (ll_to_map(ll, &map) == -1)
		exit(5);
	if (get_pos_player(&map) == -1)
		exit(6);
	if (get_collectibles_count(&map) == -1)
		exit(7);
	
	
	//TODO : if not surrounded by walls
	map_to_img(&map, &ptr);
	// print_map(map.map);
	mlx_hook(ptr.win, KeyPress, KeyPressMask, move_player, &map);
	
		
	mlx_loop(ptr.mlx);
	// while (1)
	// 	map_to_img(&map, &ptr);
}