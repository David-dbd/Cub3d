# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/27 14:32:50 by davdiaz-          #+#    #+#              #
#    Updated: 2026/07/13                                 +#+#+#+#+#+   +#+      #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc
MLX_DIR = minilibx-linux

CFLAGS = -Wall -Wextra -Werror -g -Iincludes -I$(MLX_DIR)
##SANITIZE = -fsanitize=address

# === LIBFT === #
LIBFT_DIR = lib/libft_plus
LIBFT = $(LIBFT_DIR)/libft_plus.a

# === MLX === #
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
else
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

# === COLORES === #
BOLD = \033[1m
GREEN = \033[1;92m
RED = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m

# === SOURCES === #
SRC_DIR = src

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/exit_error.c \
	$(SRC_DIR)/init_data.c \
	$(SRC_DIR)/parsing/parsing_engine.c \
	$(SRC_DIR)/parsing/figure_sections.c \
	$(SRC_DIR)/parsing/utils_figure_sections.c \
	$(SRC_DIR)/parsing/parse_paths.c \
	$(SRC_DIR)/parsing/parse_colors.c \
	$(SRC_DIR)/parsing/utils_colors.c \
	$(SRC_DIR)/parsing/parse_map.c \
	$(SRC_DIR)/parsing/extract_map_line.c \
	$(SRC_DIR)/parsing/fill_out_player.c \
	$(SRC_DIR)/parsing/utils.c \
	$(SRC_DIR)/system_search_engine/start_search_system.c \
	$(SRC_DIR)/system_search_engine/apply_search_system.c \
	$(SRC_DIR)/system_search_engine/orientation_search.c \
	$(SRC_DIR)/engine/cub3d_cleanup.c \
	$(SRC_DIR)/engine/cub3d_image.c \
	$(SRC_DIR)/engine/cub3d_init.c \
	$(SRC_DIR)/engine/cub3d_input.c \
	$(SRC_DIR)/engine/cub3d_player.c \
	$(SRC_DIR)/engine/cub3d_ray_draw.c \
	$(SRC_DIR)/engine/cub3d_ray_hit.c \
	$(SRC_DIR)/engine/cub3d_ray_init.c \
	$(SRC_DIR)/engine/cub3d_ray_texture.c \
	$(SRC_DIR)/engine/cub3d_raycast.c \
	$(SRC_DIR)/engine/cub3d_render.c \
	$(SRC_DIR)/engine/cub3d_scene.c \
	$(SRC_DIR)/engine/cub3d_start.c \
	$(SRC_DIR)/engine/cub3d_texture.c \
	$(SRC_DIR)/engine/cub3d_utils.c

OBJS = $(SRCS:src/%.c=obj/%.o)

# === REGLAS === #

all: $(LIBFT) mlx $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

mlx:
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Correctly Compiled$(RESET)"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "$(BOLD)$(RED)Objects removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re mlx