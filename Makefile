SRCS_DIR = srcs

SRCS		=	$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/utils.c	\
				$(SRCS_DIR)/utils_2.c \
				$(SRCS_DIR)/actions.c \
				$(SRCS_DIR)/actions_2.c

OBJS		=	$(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

OBJS_DIR	=	objs

NAME		=	philo

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g -pthread -fsanitize=address

RM			=	rm -rf

INC			=	-Iincludes -I/usr/include

# /* ~~~~~~~ Colors ~~~~~~~ */
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"



all:		$(NAME)

$(OBJS_DIR)/%.o :	$(SRCS_DIR)/%.c
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(SRCS) $(CFLAGS) $(INC) -o $(NAME)


clean:
			@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
			$(RM) $(OBJS)

fclean:		clean
			@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
			$(RM) $(NAME)
			$(RM) *.out
			$(RM) $(OBJS_DIR)

re:			fclean all

.PHONY:		all clean fclean re