NAME = mini_rt

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lmlx -framework OpenGL -framework AppKit

MLX_DIR = /usr/local/lib
# MLX_HEADER = $(MLX_DIR)
INCLUDES = $(MLX_DIR)/

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

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L $(MLX_DIR) $(LFLAGS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: all clean fclean re
