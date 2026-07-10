# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/27 14:32:50 by davdiaz-          #+#    #+#              #
#    Updated: 2026/07/11 01:18:49 by davdiaz-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
##SANITIZE = -fsanitize=address

# === LIBFT === #
LIBFT_DIR = lib/libft_plus
LIBFT = $(LIBFT_DIR)/libft_plus.a

# === COLORES === #
BOLD = \033[1m
GREEN = \033[1;92m
RED = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m

# === SRCS === #
SRCS = \
src/main.c \
src/exit_error.c \
src/init_data.c \
src/parsing/parsing_engine.c \
src/parsing/figure_sections.c \
src/parsing/parse_paths.c \
src/parsing/parse_colors.c \
src/parsing/parse_map.c \
src/parsing/extract_map_line.c \
src/parsing/fill_out_player.c \
src/parsing/utils.c \
src/system_search_engine/start_search_system.c \
src/system_search_engine/apply_search_system.c \
src/system_search_engine/orientation_search.c \


OBJS = $(SRCS:src/%.c=obj/%.o)

# === REGLAS === #

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)"
	@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Correctly Compiled$(RESET)"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling... $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@echo "$(BOLD)$(RED)Objects removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
