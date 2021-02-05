CC			= gcc -g
FLAGS		= -Wall -Wextra -Werror
NAME 		= minishell
DIR_LIB		= libft
LIBFT		= $(DIR_LIB)/libft.a
SRC_RT_DIR 	= ./srcs/
OBJ_DIR 	= ./objs/

SRC_RT = main.c \
			main_utils.c \
			get_next_line.c \
			launch.c \
			echo.c \
			cd.c \
			pwd.c \
			export.c \
			unset.c \
			env.c \
			exit.c \
			env_utils_1.c \
			env_utils_2.c \
			lexer.c \
			lexer_utils_1.c \
			lexer_utils_2.c \
			lexer_utils_3.c \
			token.c \
			token_utils_1.c \
			token_utils_2.c \
			parser.c \
			parser_utils.c \
			signal.c \
			error.c \
			pipe.c \
			redirect.c \
			evaluate.c \
			sort_cmd.c \
			sort_cmd_utils.c \
			realloc.c

OBJ_RT = $(addprefix $(OBJ_DIR),$(SRC_RT:%.c=%.o))
OBJ = $(OBJ_RT)
HEADERS = includes

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ_RT)
	$(CC) $(FLAGS) -I $(HEADERS) -L libft -lft $(OBJ) -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_RT_DIR)%.c
	$(CC) $(FLAGS) -I $(HEADERS) -o $@ -c $<

$(LIBFT):
	make bonus -C $(DIR_LIB)

clean :
	make clean -C $(DIR_LIB)
	rm -rf $(OBJ_DIR)

fclean : clean
	make fclean -C $(DIR_LIB)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re run
