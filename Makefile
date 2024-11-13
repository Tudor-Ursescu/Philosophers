# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 11:08:00 by tursescu          #+#    #+#              #
#    Updated: 2024/11/11 12:50:59 by tursescu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRCS = main.c utils.c init.c dinner.c getters_setters.c\
		sync_utils.c write_status.c monitor.c

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