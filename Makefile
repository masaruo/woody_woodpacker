NAME := woody_woodpacker
CC := cc
ASM := nasm
ASMFLAGS := -f elf64
CPPFLAGS := -I./include -I./libft/include
CFLAGS := -Wall -Wextra -MMD -MP
LDFLAGS :=
LIBFT := ./libft/libft.a
SRC := main.c header.c utility.c encode.c decode.c
ASM_SRC := decode_asm.s
OBJDIR := ./obj
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
ASM_OBJ := $(ASM_SRC:%.s=$(OBJDIR)/%.o)
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

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): $(OBJ) $(ASM_OBJ) $(LIBFT)
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

re: fclean all

debug: fclean
	$(MAKE) DEBUG=true

valgrind: fclean
	$(MAKE) VALGRIND=true

docker:
	docker container exec -it woody_woodpacker bash

submodule:
	git submodule update --init --recursive

-include $(DEP)

.PHONY: all clean fclean re debug valgrind
