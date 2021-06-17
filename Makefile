CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = so_long
 
SRCS_DIR = ./srcs
SRCS_NAME = main.c linked_list.c input.c img.c map.c move.c window.c err.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

INCS_DIR = ./incs

LIBFT_DIR = ./libft
LIBMLX_DIR = ./mlx
LIBFT = ft
LIBMLX = mlx
LIB_DIR = ./lib

 
MLX = $(addprefix $(MLX_DIR)/, libmlx.a)
 
 
$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) bonus
	cp $(LIBFT_DIR)/libft.a $(LIB_DIR)/
	$(MAKE) -C $(LIBMLX_DIR) all
	cp $(LIBMLX_DIR)/libmlx.dylib $(LIB_DIR)/
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIBFT) -l$(LIBMLX) -lX11 -framework OpenGL -framework AppKit $^ -o $@
#-framework OpenGL -framework AppKit $^ -o $@
 
$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

 
all : $(NAME)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMLX_DIR) clean
	rm -rf $(OBJS)
 
fclean :
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBMLX_DIR) clean
	rm -rf $(NAME) $(OBJS)
 
re : fclean all

bonus : all
 

