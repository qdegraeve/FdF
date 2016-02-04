# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 08:41:32 by qdegraev          #+#    #+#              #
#    Updated: 2016/02/04 12:39:16 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIBFTPATH = libft
LIBFT = $(LIBFTPATH)/libft.a

MLXPATH = minilibx
MLX = $(MLXPATH)/mlx.a

NAME = fdf

CC = clang

CFLAGS = -Wall -Wextra -Werror -I libft

LDFLAGS = -framework OpenGL -framework AppKit -L minilibx -lmlx -L libft -lft

SRC =  \
	./draw.c \
	./main.c \
	./pixel.c \
	./read_map.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIBFT):
	make -C $(LIBFTPATH)

$(MLX):
	make -C $(MLXPATH)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

