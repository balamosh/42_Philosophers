NAME		= philo_bonus

SRCS_DIR	= srcs/
HEAD_DIR	= includes/
BUILD_DIR	= build/

SRCS_FILES	= main.c				\
			  philo/philo_utils.c	\
			  philo/philo.c			\
			  philo/routine_utils.c	\
			  philo/routine.c		\
			  philo/time.c			\
			  libft/atol.c			\
			  libft/malloc.c		\
			  libft/memset.c		\
			  libft/swap.c

OBJS_FILES	= $(SRCS_FILES:.c=.o)

SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS		= $(addprefix $(BUILD_DIR), $(OBJS_FILES))
DEPS		= $(OBJS:.o=.d)

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -MMD -pthread 
#-fsanitize=thread -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR)%.o: $(SRCS_DIR)%.c $(BUILD_DIR)%.d
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(HEAD_DIR) -o $@ -c $<

$(BUILD_DIR)%.d: ;

$(DEPS):
-include $(wildcard $(DEPS))

clean: 
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re:
	make fclean
	make all

.PHONY: all bonus clean fclean re
