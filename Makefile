NAME = pipex.a
SOURCES = main.c \ pipex.c

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = pipex.h
RM = rm -rf                                                     

all: $(NAME)

$(NAME) : $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean:                                                                          
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re