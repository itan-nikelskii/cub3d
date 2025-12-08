NAME		:= cub3D
CC			:= cc
CFLAGS		:= -Wextra -Wall -Werror
MLX_DIR		:= MLX42
MAKEFLAGS	+= --no-print-directory
HEADERS		:= -I $(MLX_DIR)/include
LIB_MLX		:= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		:= visuals1.c
# LIBFT_DIR	:= libft
# LIBFT_ARC	:= $(LIBFT_DIR)/libft.a
OBJS		:= ${SRCS:.c=.o}

all: MLX_DIR $(NAME)

MLX_DIR:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(MLX_DIR)
	@$(CC) $(OBJS) $(LIB_MLX) $(HEADERS) -o $(NAME)

# use these when we've decided on a LIBFT

# $(NAME): $(OBJS) $(MLX_DIR) $(LIBFT_ARC)
# 	@$(CC) $(OBJS) $(LIB_MLX) $(LIBFT_ARC) $(HEADERS) -o $(NAME)

# $(LIBFT_ARC):
# 	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(MLX_DIR)/build
# 	@cd $(LIBFT_DIR) && $(MAKE) clean

fclean: clean
	@rm -rf $(NAME)
# 	@rm -f $(LIBFT_DIR)/libft.a

re: fclean all

.PHONY: all, clean, fclean, re, MLX_DIR