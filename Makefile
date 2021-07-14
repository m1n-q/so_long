CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
 
SRCS_DIR = ./srcs
SRCS_NAME = main.c linked_list.c input.c img.c map.c move.c tools.c err.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

INCS_DIR = ./incs

LIBFT_DIR = ./libft
LIBMLX_DIR = ./mlx
LIBFT = ft
LIBMLX = mlx
LIB_DIR = ./lib

 
$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) bonus
	cp $(LIBFT_DIR)/libft.a $(LIB_DIR)/
	$(MAKE) -C $(LIBMLX_DIR) all
	cp $(LIBMLX_DIR)/libmlx.dylib $(LIB_DIR)/
	cp $(LIBMLX_DIR)/libmlx.dylib ./
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIBFT) -l$(LIBMLX) -framework OpenGL -framework AppKit $^ -o $@
 
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
	rm -rf $(LIB_DIR)/*
	rm -rf libmlx.dylib

re : fclean all

bonus : all
 

