CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NAME 		= minishell
DIR_LIB		= libft
LIBFT		= $(DIR_LIB)/libft.a
SRC_RT_DIR 	= ./srcs/
OBJ_DIR 	= ./objs/

SRC_RT = main.c \
			get_next_line.c \
			echo.c \
			cd.c \
			pwd.c \
			export.c \
			unset.c \
			env.c \
			exit.c \
			env_utils.c \
			lexer.c \
			token.c \
			parser.c \
			knoda.c

OBJ_RT = $(addprefix $(OBJ_DIR),$(SRC_RT:%.c=%.o))
OBJ = $(OBJ_RT)
HEADERS = includes

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ_RT)
	$(CC) -I $(HEADERS) -L libft -lft $(OBJ) -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_RT_DIR)%.c
	$(CC) -I $(HEADERS) -o $@ -c $<

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
