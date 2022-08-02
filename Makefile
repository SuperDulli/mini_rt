NAME = mini_rt

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lmlx -framework OpenGL -framework AppKit

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MLX_NAME = libmlx_Linux.a
	LFLAGS = -lmlx_Linux -lXext -lX11 -lm
endif
ifeq ($(UNAME), Darwin)
	MLX_NAME = libmlx.a
	LFLAGS = -lmlx -framework OpenGL -framework AppKit
endif

MLX_DIR = /usr/local/lib
# MLX_HEADER = $(MLX_DIR)

LIN_ALGEBRA_DIR = lin_algebra
LIN_ALGEBRA_NAME = lin_algebra_lib.a

INCLUDES = -I$(MLX_DIR)/ -I$(LIN_ALGEBRA_DIR)/

SRCS	= main.c
OBJDIR	= obj
OBJS	= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

clean:
	$(RM) -r *.dSYM
	$(RM) -r $(OBJDIR)
	make clean -C $(LIN_ALGEBRA_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIN_ALGEBRA_DIR)

re: fclean all

$(NAME): $(OBJS) $(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME)
	$(CC) $^ -L $(MLX_DIR) $(LFLAGS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME):
	make -C $(LIN_ALGEBRA_DIR)

.PHONY: all clean fclean re
