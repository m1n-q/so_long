/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:33:49 by mishin            #+#    #+#             */
/*   Updated: 2021/07/01 17:39:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		make_bg_img(t_param_set *set, int color)
{
	int	i;
	int	j;

	set->bg.data.img = mlx_new_image(set->ptr.mlx, \
	set->map.width * BLOCK, set->map.height * BLOCK);
	if (!set->bg.data.img)
	{
		clear_elems_img(set);
		clear_map(&set->map);
		mlx_destroy_window(set->ptr.mlx, set->ptr.win);
		return (-1);
	}
	set->bg.addr = (unsigned *)mlx_get_data_addr \
			(set->bg.data.img, &set->bg.data.bits_per_pixel, \
			&set->bg.data.line_length, &set->bg.data.endian);
	i = -1;
	while (++i < set->map.width * BLOCK)
	{
		j = -1;
		while (++j < set->map.height * BLOCK)
			set->bg.addr[i + j * (set->bg.data.line_length / 4)] = color;
	}	
	return (0);
}

int		make_elems_img(t_param_set *set)
{
	int	h;
	int	w;

	set->elems.w = mlx_png_file_to_image(set->ptr.mlx, "rsrc/walls_64.png", &h, &w);
	set->elems.c = mlx_png_file_to_image(set->ptr.mlx, "rsrc/collect_64.png", &h, &w);
	set->elems.p = mlx_png_file_to_image(set->ptr.mlx, "rsrc/player_64.png", &h, &w);
	set->elems.e = mlx_png_file_to_image(set->ptr.mlx, "rsrc/exit_64.png", &h, &w);
	set->elems.ef = mlx_png_file_to_image(set->ptr.mlx, "rsrc/exit_fail_64.png", &h, &w);
	set->elems.es = mlx_png_file_to_image(set->ptr.mlx, "rsrc/exit_success_64.png", &h, &w);
	if (set->elems.w && set->elems.c && set->elems.p && set->elems.e && set->elems.ef)
		return (0);
	else
	{
		clear_elems_img(set);
		clear_map(&set->map);
		mlx_destroy_window(set->ptr.mlx, set->ptr.win);
		return (-1);
	}
}

void	put_bg_img(t_param_set *set)
{
	mlx_clear_window(set->ptr.mlx, set->ptr.win);
	mlx_put_image_to_window(set->ptr.mlx, set->ptr.win, set->bg.data.img, 0, 0);
}

int		put_elems_img(t_param_set *set, int is_collected)
{
	int		i;
	int		j;
	void	*img;
	
	put_bg_img(set);
	i = -1;
	while (++i < set->map.height && (j = -1))
	{
		while (++j < set->map.width)
		{
			img =\
				 (set->map.map)[i][j] == '1' ? set->elems.w :\
				 (set->map.map)[i][j] == 'P' ? set->elems.p :\
				 (set->map.map)[i][j] == 'C' ? set->elems.c :\
				 (set->map.map)[i][j] == 'E' ?\
				 is_collected == NOT_COLLECTED ? set->elems.ef :\
				 is_collected == ALL_COLLECTED ? set->elems.es :\
				  								 set->elems.e :\
												 NULL;
			if (img)
				mlx_put_image_to_window(set->ptr.mlx, set->ptr.win, img, j * BLOCK, i * BLOCK);
		}
	}
	return (0);
}

void	clear_elems_img(t_param_set *set)
{
	if (set->elems.w)
		mlx_destroy_image(set->ptr.mlx, set->elems.w);
	if (set->elems.c)
		mlx_destroy_image(set->ptr.mlx, set->elems.c);
	if (set->elems.p)
		mlx_destroy_image(set->ptr.mlx, set->elems.p);
	if (set->elems.e)
		mlx_destroy_image(set->ptr.mlx, set->elems.e);
	if (set->elems.ef)
		mlx_destroy_image(set->ptr.mlx, set->elems.ef);
	if (set->elems.es)
		mlx_destroy_image(set->ptr.mlx, set->elems.es);
}
