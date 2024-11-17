CC = gcc
RM = rm -f
CFLAGS = -g #-Wall -Werror -Wextra -g #-fsanitize=address -g
OpenGL = -framework OpenGL -framework AppKit
SRC = src/mandatory/main.c\
		src/mandatory/map_reader.c\
		src/mandatory/free_errors.c\
		src/mandatory/init_textures.c\
		src/mandatory/init_colors.c\
		src/mandatory/render.c\
		src/mandatory/utils.c\
		src/mandatory/key_pres.c\
		src/mandatory/ray_utils.c\
		src/mandatory/render_utils.c\
		src/mandatory/map.c\
		src/mandatory/set_up.c\
		src/mandatory/cast_rays.c
SRC_BNS = src/bns/main.c\
		src/bns/map_reader.c\
		src/bns/set_up.c\
		src/bns/free_errors.c\
		src/bns/init_textures.c\
		src/bns/init_colors.c\
		src/bns/render.c\
		src/bns/render_things.c\
		src/bns/utils.c\
		src/bns/key_pres.c\
		src/bns/ray_utils.c\
		src/bns/init_text_utils.c\
		src/bns/render_utils.c\
		src/bns/map.c\
		src/bns/mouse.c\
		src/bns/mini_map.c\
		src/bns/cast_rays.c\
		src/bns/menu.c\
		src/bns/text.c\
		src/bns/setup_utl.c\
		src/bns/detect_player.c\
		src/bns/gun.c\
		src/bns/game.c\
		src/bns/marche.c\
		src/bns/move_player.c\
		src/bns/spr_utils.c\
		src/bns/spr_logic.c\
		src/bns/free_vars.c\
		src/bns/sprite_init.c\
		src/bns/cast_rays_spr.c

LIB = libft/libft.a
GNL = gnl/gnl.a
MLX = minilibx/libmlx.a
OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJ)
	@make all -C minilibx
	@make all -C libft
	@make all -C gnl
	$(CC) $(CFLAGS) $(OBJ) $(GNL) $(LIB) $(MLX) $(OpenGL) -o $(NAME)

bonus: $(OBJ_BNS)
	@make all -C minilibx
	@make all -C libft
	@make all -C gnl
	$(CC) $(CFLAGS) $(OBJ_BNS) $(GNL) $(LIB) $(MLX) $(OpenGL) -o $(NAME)

clean:
	@make clean -C libft
	@make clean -C gnl
	$(RM) $(OBJ)
	$(RM) $(OBJ_BNS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

bore: fclean $(OBJ_BNS) bonus

mlx:
	@make clean -C minilibx
	@make all -C minilibx

norm:
	@norminette $(SRC) cub3d.h
.PHONY: all clean fclean re