SRCS =	inits.c\
		mega_free.c\
		utils.c\
		main.c

BONUS =	inits_bonus.c\
		mega_free.c\
		utils_bonus.c\
		here_doc_bonus.c\
		main_bonus.c

LIB = libft.a

INCLUDES= -I ./includes

NAME = pipex

CC = cc 

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

VPATH=src

all: $(NAME)

bonus: $(BONUS)
	$(CC) $(CFLAGS) $(INCLUDES)  $^ $(LIB) -o $(NAME)

$(NAME): $(SRCS) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES)  $^ $(LIB) -o $(NAME)

$(LIB):
	$(MAKE) -C libft
	mv libft/$(LIB) .
	$(MAKE) -C libft clean

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME) $(LIB)

re: fclean all

re_bonus: fclean $(LIB) bonus

.PHONY: all bonus clean fclean re re_bonus
