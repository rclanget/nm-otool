OTOOL		=	./ft_otool
NM			=	./ft_nm

CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra

# OTOOL
OTOOL_SRC_PATH	=	./srcs/otool/
OTOOL_SRC_NAME	=	main.c \
				ft_otool.c \
				ft_handle_32.c \
				ft_handle_64.c \
				ft_handle_fat.c \
				ft_handle_arch_32.c \
				ft_handle_arch_64.c \
				ft_add_segment.c \
				ft_swap.c
OTOOL_SRC			=	$(addprefix $(OTOOL_SRC_PATH),$(OTOOL_SRC_NAME))

OTOOL_OBJ_PATH	=	./obj/otool/
OTOOL_OBJ_NAME	=	$(OTOOL_SRC_NAME:.c=.o)
OTOOL_OBJ			=	$(addprefix $(OTOOL_OBJ_PATH),$(OTOOL_OBJ_NAME))

# NM
NM_SRC_PATH	=	./srcs/nm/
NM_SRC_NAME	=	main.c \
				ft_nm.c \
				ft_swap.c \
				ft_macho.c \
				ft_fat.c \
				ft_arch_32.c \
				ft_arch_64.c \
				ft_print_output.c
NM_SRC			=	$(addprefix $(NM_SRC_PATH),$(NM_SRC_NAME))

NM_OBJ_PATH	=	./obj/nm/
NM_OBJ_NAME	=	$(NM_SRC_NAME:.c=.o)
NM_OBJ			=	$(addprefix $(NM_OBJ_PATH),$(NM_OBJ_NAME))

INC_PATH	=	./inc/ ./libft/includes/
INC			=	$(addprefix -I,$(INC_PATH))

LIB			=	-L ./libft -lft


all: $(OTOOL) $(NM)

$(OTOOL): $(OTOOL_OBJ)
	@$(CC) $(LDFLAGS) $(OTOOL_OBJ) $(LIB) -o $@ && \
		printf " -->> \033[32mCompilation Success: %s\033[0m             \n" "$@"|| \
		printf " -->> \033[31mCompilation Failed: %s\033[0m              \n" "$@";
	@rm -rfv $(OTOOL_OBJ_PATH)

$(OTOOL_OBJ_PATH)%.o: $(OTOOL_SRC_PATH)%.c
	@make -C libft
	@mkdir -p $(OTOOL_OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

$(NM): $(NM_OBJ)
	@$(CC) $(LDFLAGS) $(NM_OBJ) $(LIB) -o $@ && \
		printf " -->> \033[32mCompilation Success: %s\033[0m             \n" "$@"|| \
		printf " -->> \033[31mCompilation Failed: %s\033[0m              \n" "$@";

$(NM_OBJ_PATH)%.o: $(NM_SRC_PATH)%.c
	@make -C libft
	@mkdir -p $(NM_OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

otool: $(OTOOL)

nm: $(NM)

clean:
	@make clean -C libft
	@rm -rfv $(OTOOL_OBJ_PATH)
	@rm -rfv $(NM_OBJ_PATH)

fclean: clean
	@make fclean -C libft
	@rm -fv $(OTOOL)
	@rm -fv $(NM)

re: fclean all

norme:
	@norminette $(OTOOL_SRC)
	@norminette $(INC_PATH)

.PHONY: all, clean, fclean, re, norme, otool, nm