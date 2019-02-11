# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchappon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/04 16:42:46 by lchappon          #+#    #+#              #
#    Updated: 2019/02/11 18:16:34 by lchappon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

NAME = wolf3d

LIB_PATH = ./libft/
INC_PATH = ./includes/
SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
MLX_PATH = ./minilibx/

INC_NAME = wolf3d.h
SRC_NAME = main.c \
		   check_file.c \
		   check_map.c \
		   draw.c \
		   raycasting.c \
		   render.c \
		   hook.c \
		   movement.c
OBJ_NAME = $(SRC_NAME:.c=.o)

INC = $(addprefix $(INC_PATH),$(INC_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -framework OpenGL -framework Appkit

all : $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_PATH)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -c -o $@ $<

$(NAME) : $(OBJ)
	make -C $(LIB_PATH)
	make -C $(MLX_PATH)
	$(CC) -o $@ $(FRAMEWORK) -L $(LIB_PATH) -lft -L $(MLX_PATH) -lmlx $^

clean :
	make -C $(LIB_PATH) clean
	make -C $(MLX_PATH) clean
	/bin/rm -rf $(OBJ_PATH)

fclean : clean
	make -C $(LIB_PATH) fclean
	/bin/rm -rf $(NAME)

re : fclean all
