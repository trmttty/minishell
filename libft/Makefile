NAME = libft.a
SRCS_M = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_putchar.c ft_putstr.c ft_isupper.c ft_islower.c ft_tabfree.c \
		ft_atof.c ft_strcmp.c ft_tabsize.c
OBJECTS_M = $(SRCS_M:.c=.o)
OBJECTS_B = $(SRCS_B:.c=.o)
HEADER = libft.h
FLAGS =	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS_M)
	ar rcs $@ $^

bonus: $(OBJECTS_M) $(OBJECTS_B)
	ar rcs $(NAME) $^

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@ -include $(HEADER)

clean:
	rm -f $(OBJECTS_M) $(OBJECTS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
