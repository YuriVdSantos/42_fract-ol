# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yvieira- <yvieira-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/09 12:35:23 by yvieira-          #+#    #+#              #
#    Updated: 2025/05/08 20:54:50 by yvieira-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

LIBFTDIR = libft

SRC = main.c math.c render.c utils.c init.c handlers.c
OBJ = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -g -I/minilibx -Wall -Wextra -Werror -I$(LIBFTDIR)
LDFLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -L$(LIBFTDIR) -lft

LIBFT = $(LIBFTDIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
		rm -f $(OBJ)
		$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
		rm -f $(NAME)
		$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all