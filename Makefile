NAME := woody_woodpacker
CC := cc
CPPFLAGS := -I./include -I./libft/include
CFLAGS := -Wall -Wextra -MMD -MP
LDFLAGS := 
LIBFT := ./libft/libft.a
SRC := main.c header.c utility.c
OBJDIR := ./obj
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
DEP := $(SRC:%.c=$(OBJDIR)/%.d)

vpath %.c ./src

ifeq ($(DEBUG), true)
	CFLAGS += -ggdb -O0 -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
else ifeq ($(VALGRIND), true)
	CFLAGS += -g -O0
else
	CFLAGS += -Werror -pedantic
endif

all: $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJ) $(LIBFT) -o $@

$(OBJDIR):
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) clean -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

debug: fclean
	$(MAKE) DEBUG=true

valgrind: fclean
	$(MAKE) VALGRIND=true

docker:
	docker container exec -it woody_woodpacker bash

-include $(DEP)

.PHONY: all clean fclean re debug valgrind
