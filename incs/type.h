#ifndef TYPE_H
# define TYPE_H

typedef struct	s_elems
{
	void		*w;
	void		*c;
	void		*p;
	void		*e;
}				t_elems;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_ptr 
{
	void		*mlx;
	void		*win;
}				t_ptr;

typedef struct	s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct	s_map
{
	int			width;
	int			height;
	t_vector	pos;
	char		**map;
	int			collectibles;
	int			walls;
	int			fin;
}				t_map;

typedef struct	s_bg
{
	t_data		data;
	unsigned	*addr;
}				t_bg;

typedef struct	s_ll
{
	char	c;
	struct s_ll	*next;
}				t_ll;

typedef struct	s_param_set
{
	t_map		map;
	t_ptr		ptr;
	t_elems		elems;
	t_bg		bg;
}				t_param_set;
#endif