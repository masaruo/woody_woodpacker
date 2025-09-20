NAME := woody_woodpacker
CC := cc
CPPFLAGS := -I./include -I./libft/include
CFLAGS := -Wall -Wextra -MMD -MP
LDFLAGS :=
LIBFT := ./libft/libft.a
SRC := main.c parser.c utility.c inject.c encode.c
OBJDIR := ./obj
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
DEP := $(SRC:%.c=$(OBJDIR)/%.d)

vpath %.c ./src
vpath %.s ./src

ifeq ($(DEBUG), true)
	CFLAGS += -ggdb -O0 -fsanitize=address,undefined
	ASMFLAGS += -g
	LDFLAGS += -fsanitize=address,undefined
else ifeq ($(VALGRIND), true)
	CFLAGS += -ggdb -O0
	ASMFLAGS += -g
else
	CFLAGS += -Werror -pedantic
endif

all: $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(MAKE) stub
	$(CC) $(LDFLAGS) $(ASM_OBJ) $(OBJ) $(LIBFT) -o $@

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
	$(RM) woody

re: fclean all

debug: fclean
	$(MAKE) DEBUG=true

valgrind: fclean
	$(MAKE) VALGRIND=true

docker:
	docker container exec -it --user 1000 woody_woodpacker bash

submodule:
	git submodule update --init --recursive

stub: | $(OBJDIR)
	nasm -f bin ./src/stub.s -o ./obj/stub.bin
	xxd -i ./obj/stub.bin > ./include/stub.h

-include $(DEP)

.PHONY: all clean fclean re debug valgrind
