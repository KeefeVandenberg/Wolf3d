# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvandenb <kvandenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/12 18:14:56 by kvandenb          #+#    #+#              #
#    Updated: 2018/03/06 18:26:35 by kvandenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

libx_flags = -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

cflags = -Wall -Wextra -Werror -lpthread -fsanitize=address

make_libft = @make -C ./GNL/libft/

header = wolf3d.h

includes = ./GNL/libft/libft.a ./GNL/get_next_line.c ./minilibx_macos/libmlx.a

SRC = main.c open_map.c draw.c utils.c

OBJ = *.o

cc = @gcc

name = wolf3d

all: $(name)

$(name):
	
	$(make_libft)
	$(cc) $(libx_flags) -g $(SRC) $(includes) -o $(name)
	@echo "Created Wolf3d executable"

clean:
	@make -C GNL/libft/ clean
	@/bin/rm -f $(name)

fclean:
	@make -C GNL/libft/ fclean

re : clean fclean all
