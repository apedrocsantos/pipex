SRCS =	inits.c\
		mega_free.c\
		utils.c\
		main.c

BONUS =	inits_bonus.c\
		mega_free.c\
		utils_bonus.c\
		here_doc_bonus.c\
		main_bonus.c

LIB = -L . -lft gnl.a

INCLUDES= -I ./includes

NAME = pipex

CC = cc 

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

VPATH=src

all: $(NAME)

bonus: $(BONUS)
	$(CC) $(CFLAGS) $(INCLUDES)  $^ $(LIB) -o $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES)  $^ $(LIB) -o $(NAME)

libft:
	$(MAKE) -C libft
	mv ./libft/libft.a .

fclean:
	rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: all fclean re re_bonus libft
