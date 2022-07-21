NAME = mini_rt

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lmlx -framework OpenGL -framework AppKit

MLX_DIR = /usr/local/lib
# MLX_HEADER = $(MLX_DIR)
INCLUDES = $(MLX_DIR)/

LIN_ALGEBRA_DIR = lin_algebra
LIN_ALGEBRA_NAME = lin_algebra_lib.a

SRCS	= main.c
OBJDIR	= obj
OBJS	= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

clean:
	$(RM) -r *.dSYM
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS) $(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME)
	$(CC) $(OBJS) $(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME) -L $(MLX_DIR) $(LFLAGS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME):
	make -C $(LIN_ALGEBRA_DIR)

.PHONY: all clean fclean re
