NAME = lin_algebra_lib.a

TEST = tests
TESTS = $(wildcard $(TEST)/*.c)
TESTBINS = $(patsubst $(TEST)/%.c,$(TEST)/bin/%,$(TESTS))

VECTOR_N= $(TEST)/bin/vector_test
VECTOR	= vector.c \
			length.c \
			length_squared.c \
			scalar_mult.c \
			normalize.c \
			add.c sub.c \
			dot.c \
			is_zero.c \
			is_equal.c \
			cross.c \
			copy.c \
			clamp.c \
			shift.c
VECTOR_S= $(addprefix vector/,$(VECTOR))
VECTOR_T= $(VECTOR_S) $(TEST)/vector_test.c

MATRIX_N= $(TEST)/bin/matrix_test
MATRIX	= matrix.c \
			scalar_mult.c \
			mult.c \
			add.c \
			transpose.c \
			determinant.c \
			inverse.c \
			scale.c \
			translate.c \
			rotate.c
MATRIX_S= $(addprefix matrix/,$(MATRIX))
MATRIX_T= $(MATRIX_S) $(TEST)/matrix_tests.c

SRCS	= $(VECTOR_S) $(MATRIX_S)
HEADERS	= $(patsubst %.c,%.h,$(SRCS))
OBJDIR	= obj
OBJS	= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -lm

all: $(NAME)
	make clean
# all: $(VECTOR_N) $(MATRIX_N)

clean:
	$(RM) -r *.dSYM
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(VECTOR_N)
	$(RM) $(MATRIX_N)
	$(RM) -r $(TEST)/bin

re: fclean all

show:
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)

test: v m

v: $(VECTOR_N)
	./$^ --verbose

m: $(MATRIX_N)
	./$^

$(NAME): $(OBJS)
	ar -cr $@ $(OBJS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/vector
	mkdir $(OBJDIR)/matrix

$(TEST)/bin:
	mkdir $@

$(VECTOR_N): $(VECTOR_T) | $(TEST)/bin
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS) -lcriterion

$(MATRIX_N): $(MATRIX_T) | $(TEST)/bin
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS) -lcriterion

.PHONY: all clean fclean re show v m test
