CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread
THFLAG = -lpthread
NAME = philo
OBJS_DIR := objs
SRCS = srcs/check.c\
		srcs/error.c\
		srcs/free.c\
		srcs/init.c\
		srcs/main.c\
		srcs/monitor.c\
		srcs/routine.c\
		srcs/utils.c\

OBJS = ${SRCS:srcs/%.c=$(OBJS_DIR)/%.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(THFLAG) $(OBJS) -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: srcs/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

