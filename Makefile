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

LIBS = $(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME) $(LIBFT_DIR)/$(LIBFT_NAME) $(MLX_DIR)/$(MLX_NAME)
INCLUDES = -I$(MLX_DIR) -I$(LIN_ALGEBRA_DIR) -I$(LIBFT_DIR)

SRCS	= 	camera.c \
			check_elements.c \
			check_file.c \
			check_info.c \
			check_utils.c \
			color.c \
			cylinder.c \
			intersection.c \
			light.c \
			main.c \
			object.c \
			plane.c \
			ray.c \
			render.c \
			scene.c \
			sphere.c \
			store_data.c \
			store_elements.c \
			transform.c \
			utils.c
ifeq ($(UNAME), Linux)
	SRCS := $(SRCS) close_window_linux.c
endif
ifeq ($(UNAME), Darwin)
	SRCS := $(SRCS) close_window_mac.c
endif

OBJDIR	= obj
OBJS	= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
OBJS_NO_MAIN = $(filter-out obj/main.o, $(OBJS)) # useful for building tests

TEST = tests
TESTS = $(wildcard $(TEST)/*.c)
TESTBINS = $(patsubst $(TEST)/%.c,$(TEST)/bin/%,$(TESTS))
# CRITERION_VERBOSITY_LEVEL = 1

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
	make clean -C $(LIN_ALGEBRA_DIR) --quiet
	make clean -C $(LIBFT_DIR) --quiet

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(TEST)/bin
	make fclean -C $(LIN_ALGEBRA_DIR) --quiet
	make fclean -C $(LIBFT_DIR) --quiet

re: fclean all

$(NAME): $(OBJS) $(LIBS)
	$(CC) $^ $(LFLAGS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(TEST)/bin/%: $(OBJS_NO_MAIN) $(TEST)/%.c  $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -lcriterion $(LFLAGS) -o $@

$(TEST)/bin:
	mkdir $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIN_ALGEBRA_DIR)/$(LIN_ALGEBRA_NAME):
	make -C $(LIN_ALGEBRA_DIR) --quiet

$(LIBFT_DIR)/$(LIBFT_NAME):
	make -C $(LIBFT_DIR) --quiet

leaks: $(NAME) scenes/test.rt
	$(LEAKS) ./$(NAME) scenes/test.rt

test: $(TEST)/bin $(TESTBINS)
	@for test in $(TESTBINS) ; do ./$$test --verbose; done

.PHONY: all clean fclean re leaks test
