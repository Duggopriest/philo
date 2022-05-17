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

#should die
test1:
	make
	@echo running
	@./philo 1 800 200 200

#should live
test2:
	make
	@echo running
	@./philo 5 800 200 200

#should live
test3:
	make
	@echo running
	@./philo 5 800 200 200 7

#should live
test4:
	make
	@echo running
	@./philo 4 410 200 200

#One philosopher should die.
test5:
	make
	@echo running
	@./philo 4 310 200 100

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
	@norminette