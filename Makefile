SRCS	=	srcs/pipex_main.c \
			srcs/pipex_utils.c \
			srcs/get_next_line.c \
			srcs/get_next_line_utils.c \

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes/

NAME	=	pipex

LNAME	=	libft/libft.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c ./includes/get_next_line.h ./includes/pipex.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS) ./libft/libft.h
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