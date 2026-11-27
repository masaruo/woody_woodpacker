.PHONY: all clean fclean re debug valgrind test
.DELETE_ON_ERROR:

NAME := woody_woodpacker
CC := cc
OBJDIR := ./obj
CPPFLAGS := -I./include -I./libft/include -I$(OBJDIR)
CFLAGS := -Wall -Wextra -MMD -MP
LDFLAGS :=
LIBFT := ./libft/libft.a
SRC := main.c parser.c utility.c inject.c rc4.c
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
DEP := $(SRC:%.c=$(OBJDIR)/%.d)
STUB_BIN := $(OBJDIR)/stub.bin
STUB_H :=  $(OBJDIR)/stub.h

vpath %.c ./src

ifeq ($(DEBUG), true)
	CFLAGS += -ggdb -O0 -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
else ifeq ($(VALGRIND), true)
	CFLAGS += -ggdb -O0
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
	$(RM) woody

re:
	$(MAKE) fclean
	$(MAKE) all

debug: fclean
	$(MAKE) DEBUG=true

valgrind: fclean
	$(MAKE) VALGRIND=true

$(STUB_BIN): ./src/stub.s ./src/rc4.s | $(OBJDIR)
	nasm -f bin ./src/stub.s -o $@

$(STUB_H): $(STUB_BIN) | $(OBJDIR)
	echo "#pragma once" > $@
	xxd -i $(STUB_BIN) >> $@

$(OBJDIR)/inject.o: $(STUB_H)

test:
	$(MAKE) fclean
	$(MAKE) debug
	./woody_woodpacker resources/sample
	./woody

-include $(DEP)