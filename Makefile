# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/24 13:52:49 by mbenjell          #+#    #+#              #
#    Updated: 2019/04/07 13:16:39 by mbenjell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

INC =	defaults.h \
		types.h \
		prototypes.h

_SRC =	libft_mem.c \
		libft_str.c \
		main.c \
		init.c \
		quadric.c \
		quadric_list.c \
		quadric_list_specials.c \
		instance.c \
		tools.c \
		transformation.c \
		parse.c \
		store.c \
		preset.c \
		stream.c \
		matrix.c \
		mat3.c \
		vec3.c \
		vec3_ext.c \
		vec3_ter.c \
		vec4.c \
		events.c \
		input.c \
		render.c \
		render_data.c \
		raytrace.c \
		filtre.c \
		filtre2.c \
		csg.c \
		qunion.c \
		qunion_extra.c \
		texture.c \
		mapping.c \
		perturbation.c \
		edit.c \
		perlin.c \
		direct_light.c \
		intersection.c \
		quadric_math.c \
		lighting.c

SRC = 		$(addprefix src/, $(_SRC))

LIBMLX_MACOS = ./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
LIBMLX_LINUX = ./minilibx-linux/libmlx.a -lX11 -lXext

FLAG =		-O3 -Wall -Wextra -Werror -Iincludes

RM = 		/bin/rm -f

OBJ = 		$(addsuffix .o,$(basename $(SRC)))

.PHONY: all clean fclean re

all: 		$(NAME)

%.o : 		%.c $(addprefix includes/, $(INC))
			clang -c $(FLAG) -o $@ $<

$(NAME): 	$(OBJ)
			@echo "Building minilibx-linux."
			@make -C minilibx-linux
			@echo "Linking."
			@clang $(FLAG) -lpthread -lm $(OBJ) -o $(NAME) $(LIBMLX_LINUX)

clean:
			make clean -C minilibx-linux
			@$(RM) $(OBJ)

fclean:		clean
			make clean -C minilibx-linux
			@$(RM) $(NAME)

re:			fclean all

fcleanme:
			@$(RM) $(OBJ)
			@$(RM) $(NAME)

reme: fcleanme all
