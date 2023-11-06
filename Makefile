NAME	:= FDF
CFLAGS	:= -Wextra -Wall -Werror #-Wunreachable-code -Ofast -w
LIBMLX	:= ./lib/MLX42
LIBFT	:= libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -mmacosx-version-min=12.6 $(LIBFT)
SRCS	:= main.c
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
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "...Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) 

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