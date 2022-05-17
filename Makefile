# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 13:29:03 by jgobbett          #+#    #+#              #
#    Updated: 2022/05/17 12:54:48 by jgobbett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c
INCS = -I philo.h
FLAGS = -pthread -Wall -Wextra -Werror
NAME = philo

all:
	@clear
	@echo -n Compiling philo...
	@gcc $(SRC) $(FLAGS) -o $(NAME)
	@echo Done
	@echo running
	./philo 1 1000 100 100

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