NAME = cube3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_DIR = src
INCL_DIR =	include
LIBFTDIR = libft
OBJ_DIR = obj

LIBFT = $(LIBFTDIR)/libft.a

SRCS =  map_validation.c \
		parser.c \
		utils.c \

# Add directory prefixes
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I$(INCL_DIR) -I$(LIBFTDIR)

# Default target
all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Place all .o in obj/ 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create obj/ directory (-p for path w/o error if the dir already exists)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build libft library
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re