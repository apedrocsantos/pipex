SRCS =	find_path.c\
		mega_free.c\
		main.c

LIB = -L . -lft

INCLUDES= -I ./includes

NAME = pipex

CC = cc 

CFLAGS = -Wall -Werror -Wextra -g

VPATH=src

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES)  $^ $(LIB) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean re 
