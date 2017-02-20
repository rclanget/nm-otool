NAME		=	./ft_otool

CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra

SRC_PATH	=	./srcs/otool/
SRC_NAME	=	main.c \
				ft_otool.c \
				ft_option.c \
				tools.c \
				ft_handle_64.c
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_PATH	=	./obj/
OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC_PATH	=	./inc/
INC			=	$(addprefix -I,$(INC_PATH))



all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $@ && \
		printf " -->> \033[32mCompilation Success: %s\033[0m             \n" "$@"|| \
		printf " -->> \033[31mCompilation Failed: %s\033[0m              \n" "$@";

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

clean:
	@rm -rfv $(OBJ_PATH)

fclean: clean
	@rm -fv $(NAME)

re: fclean all

norme:
	@norminette $(SRC)
	@norminette $(INC_PATH)

.PHONY: all, clean, fclean, re, norme