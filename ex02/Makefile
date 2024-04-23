NAME 		= 	Pmergeme

SRCS		=	main.cpp PmergeMe.cpp
OBJS		=	$(SRCS:.cpp=.o)

CC = c++
CFLAGS =  -gdwarf-4 -std=c++98
 CFLAGS += -g3 
# CFLAGS += -fsanitize=address
ifeq ($(DEBUG),true)
	CFLAGS += -g
endif
OCFLAGS		=	-Wall -Wextra -Werror

all:	 		$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OCFLAGS) $(OBJS) -o $@

%.o: %.cpp
	 $(CC) $(CFLAGS) -c $< -o $@

clean:
				@rm -f $(OBJS)

fclean: 		clean
				@rm -f $(NAME)

re: 			fclean all
