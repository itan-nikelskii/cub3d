# **************************************************************************** #
#                              COMPILER CONFIG                                 #
# **************************************************************************** #
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# **************************************************************************** #
#                               DIRECTORIES                                    #
# **************************************************************************** #

SRC_DIR = src
INCL_DIR = include
LIBFTDIR = libft
OBJ_DIR = obj
MLX_DIR	= MLX42

# **************************************************************************** #
#                              SOURCE FILES                                    #
# **************************************************************************** #
# Parser sources
PARSER_SRCS =	parser/parser.c \
				parser/utils_map.c \
				parser/utils_parser.c \
				parser/validation_map.c \
				parser/validation_scene.c

# Visualisation sources
VISUALS_SRCS =	visuals/visuals.c \
				visuals/visualisation_utils.c \
				visuals/init_ray.c \
				visuals/visualise_line.c \
				visuals/dda.c

# Movement / key-handling sources
KEY_SRCS = key_events/key_handler.c \
				key_events/player_movement.c

# Other sources
OTHER_SRCS =	main.c \
				init.c \
				utils.c \
				minimap.c

# All sources
SRCS = $(PARSER_SRCS) $(VISUALS_SRCS) $(KEY_SRCS) $(OTHER_SRCS)

# **************************************************************************** #
#                                LIBRARIES                                     #
# **************************************************************************** #
LIBFT = $(LIBFTDIR)/libft.a
LIB_MLX	= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

# **************************************************************************** #
#                                   MAKE                                       #
# **************************************************************************** #

# Add directory prefixes
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I $(INCL_DIR) -I $(LIBFTDIR)

# Default target
all: LIB_MLX $(OBJ_DIR) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_MLX) $(LIBFT) -o $(NAME)

# Place all .o in obj/ (auto-create needed subdirs)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create obj/ directory (-p for path w/o error if the dir already exists)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build libft library
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# # Clone MLX_DIR
# $(MLX_DIR):
# 	git clone https://github.com/codam-coding-college/MLX42.git

# # Build MLX library
# LIB_MLX: $(MLX_DIR)
# 	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

# Build MLX library
LIB_MLX:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re