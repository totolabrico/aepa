# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 16:29:22 by tbarbe            #+#    #+#              #
#    Updated: 2022/07/25 18:21:31 by tbarbe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pedal

SRCS	= 	srcs/*.cpp

CC		= c++

RM		= rm -f

CFLAGS	= -lasound -lpthread

${NAME}:	${OBJS}
					${CC} -o ${NAME} ${SRCS} ${CFLAGS}

all:		${NAME}

fclean:
						${RM} $(NAME)

re:						fclean all

.PHONY:		all fclean re
