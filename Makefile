# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 13:29:03 by jgobbett          #+#    #+#              #
#    Updated: 2022/05/15 20:35:36 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c
INCS = -I philo.h
FLAGS = -Wall -Wextra -Werror
NAME = philo

all:
	@clear
	@echo -n Compiling push_swap...
	@gcc $(SRC) $(INCS) $(FLAGS) -o $(NAME)
	@echo Done

git:
	@clear
	@git add .
	@echo "commit msg" 
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

clean:
	@rm -rf $(NAME)

norm:
	@clear
	@norminette $(INCS) $(SRC)