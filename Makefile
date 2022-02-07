SRCS	=	srcs/pipex_main.c \
			srcs/pipex_utils.c \
			srcs/get_next_line.c \
			srcs/get_next_line_utils.c \

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes/pipex.h

NAME	=	pipex

LNAME	=	libft/libft.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@ -I$(HEADS)

$(NAME): $(OBJS)
	$(MAKE) -C libft all
	$(GCC) $(FLAGS) $(OBJS) $(LNAME) -o $(NAME)

all:	$(NAME)

clean:
		$(MAKE) -C libft clean
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all