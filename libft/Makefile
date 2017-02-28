# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/08 20:12:26 by rclanget          #+#    #+#              #
#    Updated: 2017/01/08 20:36:29 by rclanget         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

IDIR		=	includes/

SRC_PATH	=	sources/
SRC_NAME	= 	ft_atoi.c ft_bzero.c ft_escape.c ft_isalnum.c ft_isalpha.c \
				ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c \
				ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
				ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
				ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
				ft_nbrlen.c ft_option.c ft_putchar.c ft_putchar_fd.c \
				ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
				ft_putstr_fd.c ft_realloc.c ft_strcat.c ft_strchr.c \
				ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c \
				ft_striter.c ft_striteri.c ft_strjoin.c ft_strjoin_woc.c \
				ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
				ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
				ft_strrev.c ft_strsplit.c ft_strsplit_custom.c ft_strstr.c \
				ft_strtrim.c ft_tolower.c ft_toupper.c get_next_line.c \
				ft_putstr.c ft_strlcat.c ft_strsub.c ft_isupper.c ft_print.c \
				ft_strclr.c ft_strrchr.c ft_error.c ft_printf.c
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ 		=	$(SRC:.c=.o)

FLAGS 		=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ) && ranlib $(NAME) && \
		printf " -->> \033[32mCompilation Success: %s\033[0m             \n" "$@"|| \
		printf " -->> \033[31mCompilation Failed: %s\033[0m              \n" "$@";

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< -I $(IDIR) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
