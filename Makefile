# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/12 18:14:56 by kvandenb          #+#    #+#              #
#    Updated: 2018/03/21 17:02:47 by kvandenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

libx_flags = -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

cflags = -Wall -Wextra -Werror -lpthread

make_libft = @make -C ./GNL/libft/

make_mlx = @make -C ./minilibx_macos/

header = wolf3d.h

includes = ./GNL/libft/libft.a ./GNL/get_next_line.c ./minilibx_macos/libmlx.a

SRC = main.c open_map.c draw.c utils.c mini_map.c init.c movement.c

OBJ = *.o

cc = @gcc

name = wolf3d

all: $(name)

$(name):
	@$(make_mlx)
	@$(make_libft)
	@$(cc) $(libx_flags) -g $(SRC) $(includes) -o $(name)
	clear
	@printf "Created Wolf3d executable\n"

clean:
	@make -C minilibx_macos/ clean
	@make -C GNL/libft/ clean
	@/bin/rm -f $(name)

fclean:
	@make -C GNL/libft/ fclean
	@make -C minilibx_macos/ clean

re : clean fclean all
