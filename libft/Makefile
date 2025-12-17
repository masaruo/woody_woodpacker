# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2023/12/13 10:28:15 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
CFLAGS		:=	-Wall -Wextra -Werror -g -MMD -MP
AR			:=	ar rcs
FILES		:=	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset \
				ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_toupper ft_tolower ft_strlcat \
				ft_strchr ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi \
				ft_calloc ft_strdup \
				ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
				ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
				ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone \
				ft_lstclear ft_lstiter ft_lstmap \
				ft_strcmp ft_cntchar ft_free_null ft_isspace ft_swap ft_get_int \
				ft_lalloc ft_lalloc_utils ft_lstcalloc
SRCS_DIR	:=	./src/
OBJS_DIR	:=	./obj/
INC_DIR		:=	./include
SRCS		:=	$(addsuffix .c, $(FILES))
OBJS		:=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
DEPS		:=	$(SRCS:%.c=$(OBJS_DIR)%.d)

ifdef WITH_DEBUG
CFLAGS := -Wall -Wextra -g3 -O0
endif

ifdef WITH_ASAN
CFLAGS := -Wall -Wextra -g3 -O0 -fsanitize=address
endif

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus: 
	make $(NAME)

debug: fclean
	make $(NAME) WITH_DEBUG=1

asan: fclean
	make $(NAME) WITH_ASAN=1

all: $(NAME)

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re debug asan



