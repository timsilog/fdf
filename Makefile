# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjose <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/21 14:51:55 by tjose             #+#    #+#              #
#    Updated: 2017/03/09 17:41:49 by tjose            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = fdf
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = $(addprefix $(SRCDIR), $(SRCFILES))
OBJS = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))
SRCFILES = main.c \
		   matrix.c \
		   rotate.c \
		   draw.c \
		   parse.c \
		   draw_pic.c \
		   colors.c
SRCDIR = ./srcs/
OBJDIR = ./objs/
INCDIR = ./includes/
LIBFTL = -L./libft -lft
MLXL = -L./minilibx_macos -lmlx

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJS)
	make -C ./minilibx_macos
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTL) $(MLXL) -o $(NAME) -framework OpenGL -framework AppKit
	
clean:
	make -C ./libft clean
	make -C ./minilibx_macos clean
	rm -fr $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
