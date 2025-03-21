# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 11:08:00 by tursescu          #+#    #+#              #
#    Updated: 2025/03/21 11:50:56 by tursescu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRCS = src/main.c src/utils.c src/init.c src/dinner.c src/getters_setters.c\
		src/sync_utils.c src/write_status.c src/monitor.c

CC = cc

RM = -rm -f

CFLAGS = -Wall -Wextra -Werror -pthread -g 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re