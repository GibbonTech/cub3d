# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 23:15:00 by rick              #+#    #+#              #
#    Updated: 2025/04/13 15:57:05 by ykhomsi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
CC := cc
CFLAGS := -Wall -Werror -Wextra -O3 -g -I $(LIBFT_PATH)includes
LIBMLX := ./MLX42

# Source files
SRCS :=	./src/core/main.c \
		./src/initialization/init_window.c \
		./src/initialization/init_data.c \
		./src/input/event_handler.c \
		./src/input/event_handler_keys.c \
		./src/input/event_handler_movement.c \
		./src/input/event_handler_mouse.c \
		./src/input/event_handler_position.c \
		./src/input/event_handler_position_utils.c \
		./src/parsing/parsing.c \
		./src/parsing/parsing_map.c \
		./src/parsing/parsing_map_utils.c \
		./src/parsing/parsing_map_utils2.c \
		./src/parsing/parsing_map_utils3.c \
		./src/parsing/parsing_map_utils4.c \
		./src/parsing/parsing_map_validation.c \
		./src/parsing/parsing_map_validation_utils.c \
		./src/parsing/parsing_utils.c \
		./src/parsing/parsing_identifiers.c \
		./src/parsing/parsing_identifiers_utils.c \
		./src/parsing/parsing_textures.c \
		./src/raycasting/raycasting.c \
		./src/raycasting/raycasting_utils.c \
		./src/raycasting/raycasting_textures.c \
		./src/raycasting/raycasting_floor.c \
		./src/raycasting/raycasting_floor_utils.c \
		./src/raycasting/raycasting_draw.c \
		./src/raycasting/raycasting_sections.c \
		./src/raycasting/raycasting_render.c \
		./src/raycasting/raycasting_texture_utils.c \
		./src/utils/get_next_line.c \
		./src/utils/get_next_line_utils.c \
		./src/utils/get_next_line_utils2.c \
		./src/utils/cleanup.c \
		./src/utils/cleanup_utils.c \
		./src/rendering/gun_utils.c \
		./src/rendering/gun_init.c \
		./src/rendering/gun_simple.c \
		./src/minimap/draw_map_2d_1.c \
		./src/minimap/draw_map_2d_2.c \
		./src/minimap/draw_map_2d_3.c \
		./src/minimap/draw_map_2d_4.c \
		./src/minimap/draw_map_2d_5.c \
		./src/minimap/draw_map_2d_6.c \
		./src/minimap/draw_map_2d_7.c \
		./src/minimap/draw_map_2d_8.c

LIBFT_PATH := libft/
LIBFT_NAME := libft.a
LIBFT_FLAGS := -L$(LIBFT_PATH) -lft
LIBFT := $(LIBFT_PATH)$(LIBFT_NAME)

MLX_PATH := MLX42/build/
MLX_NAME := libmlx42.a
HEADERS := -I ./include -I $(LIBMLX)/include
MLX_FLAGS := -L$(MLX_PATH) -lmlx42 -ldl -lglfw -pthread -lm
MLX := $(MLX_PATH)$(MLX_NAME)

BIN_DIR := bin

OBJS := $(SRCS:./src/%.c=$(BIN_DIR)/%.o)

all: $(MLX_PATH) $(NAME)

$(BIN_DIR)/core/%.o: ./src/core/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BIN_DIR)/initialization/%.o: ./src/initialization/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BIN_DIR)/input/%.o: ./src/input/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BIN_DIR)/parsing/%.o: ./src/parsing/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BIN_DIR)/raycasting/%.o: ./src/raycasting/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BIN_DIR)/utils/%.o: ./src/utils/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BIN_DIR)/rendering/%.o: ./src/rendering/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BIN_DIR)/minimap/%.o: ./src/minimap/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(MLX_PATH):
	@mkdir -p $(MLX_PATH)
	@cmake $(LIBMLX) -B $(MLX_PATH) && make -C $(MLX_PATH) -j4

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH) all
	@$(CC) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "$(NAME) successfully compiled!"

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)/core
	@mkdir -p $(BIN_DIR)/initialization
	@mkdir -p $(BIN_DIR)/input
	@mkdir -p $(BIN_DIR)/parsing
	@mkdir -p $(BIN_DIR)/raycasting
	@mkdir -p $(BIN_DIR)/utils
	@mkdir -p $(BIN_DIR)/rendering
	@mkdir -p $(BIN_DIR)/minimap

clean:
	@rm -rf $(OBJS)
	@rm -rf $(MLX_PATH)
	@make -C $(LIBFT_PATH) clean
	@echo "Object files removed!"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(NAME) removed!"

re: fclean all

.PHONY: all clean fclean re