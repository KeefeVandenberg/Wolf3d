# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/12 18:14:56 by kvandenb          #+#    #+#              #
#    Updated: 2018/03/22 14:54:09 by kvandenb         ###   ########.fr        #
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
	@printf "\e[1;31mMaking libft\e[0m\n"
	@$(make_libft)
	@printf "\e[1;31mMaking wolf3d\e[0m\n"
	@$(cc) $(libx_flags) $(cflags) -g $(SRC) $(includes) -o $(name)
	@printf "\e[1;32mCreated Wolf3d executable\e[0m\n"

clean:
	@make -C minilibx_macos/ clean
	@make -C GNL/libft/ clean
	@/bin/rm -f $(name)
	@printf "\e[36mNice and clean\e[0m\n"

fclean:
	@make -C GNL/libft/ fclean
	@make -C minilibx_macos/ clean
	@printf "\e[35mEven cleaner\e[0m\n"

re : clean fclean all
