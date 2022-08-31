NAME = miniRT

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

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

LIBFT_DIR = libft
LIBFT_NAME = libft.a

INCLUDES = -I$(MLX_DIR)/ -I$(LIN_ALGEBRA_DIR)/ -I$(LIBFT_DIR)

SRCS	= main.c \
			utils.c \
			float_utils.c \
			color.c \
			check_file.c \
			check_elements.c \
			check_info.c \
			check_utils.c \
			store_data.c \
			store_eöements.c \
			object.c \
			camera.c \
			light.c \
			sphere.c \
			cylinder.c \
			plane.c \
			scene.c \
			transform.c
# SRCS	= color.c # test only one file with included main check_elements.c check_utils.c check_info.c
OBJDIR	= obj
OBJS	= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
ifeq ($(UNAME), Linux)
	LEAKS = valgrind $(VALGRIND_FLAGS)
endif
ifeq ($(UNAME), Darwin)
	LEAKS = leaks --atExit --
endif

all: $(NAME)

clean:
	$(RM) -r *.dSYM
	$(RM) -r $(OBJDIR)
	make clean -C $(LIN_ALGEBRA_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIN_ALGEBRA_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

$(NAME): $(OBJS) $(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME) $(LIBFT_DIR)/$(LIBFT_NAME)
	$(CC) $^ -L $(MLX_DIR) $(LFLAGS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME):
	make -C $(LIN_ALGEBRA_DIR)

$(LIBFT_DIR)/$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

leaks: $(NAME) test.rt
	$(LEAKS) ./$(NAME) test.rt

.PHONY: all clean fclean re leaks
