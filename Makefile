CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = container

Header = Bst.hpp Avl.hpp

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp  $(Header)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(Header)
	$(CC) $(CFLAGS) -o $(NAME)  $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
