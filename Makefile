# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:45:13 by sde-silv          #+#    #+#              #
#    Updated: 2023/11/13 15:45:17 by sde-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror #-Wunreachable-code -Ofast -w
LIBMLX	:= ./lib/MLX42
LIBFT	:= libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -mmacosx-version-min=12.6 $(LIBFT)
SRCS	:= main.c ft_map_parser.c ft_parser_utils.c ft_calc_coords.c
OBJS	:= $(SRCS:.c=.o)
GIT     := 	if [ -d $(LIBMLX) ]; \
			then git -C $(LIBMLX) pull; \
			else git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
			fi

all: libmlx libft $(NAME)

libmlx:
	@echo "...Checking for MLX42 repo updates."
	@$(GIT)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C ./lib/libft
	@cp lib/libft/$(LIBFT) $(LIBFT)
	@cp lib/libft/libft.h include/libft.h

%.o: %.c
	@$(CC) -g $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "...Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) -g $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) 

clean:
	@rm -rf $(OBJS)
	@echo "...FDF OBJs cleaned."

fclean: clean
	@rm -rf $(NAME)
	@echo "...FDF binary cleaned."
	@rm -rf $(LIBMLX)/build
	@echo "...MLX42 build files cleaned."
	@$(MAKE) fclean -C ./lib/libft
	@rm -f libft.a

re: clean all

.PHONY: all, clean, fclean, re
