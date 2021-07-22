# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 16:44:37 by aperez-b          #+#    #+#              #
#    Updated: 2021/07/22 18:34:54 by aperez-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

UNAME = $(shell uname -s)
ECHO = echo
ifeq ($(UNAME), Linux)
	ECHO = echo -e
endif

CFLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = gcc
DIR_M = mandatory
DIR_GNL = get_next_line
DIR_B = bonus
DIR_OBJ = lib
LIBFT = libft.a
NAME = so_long

SOURCE_M = errors.c #map.c

SOURCE_GNL = get_next_line.c get_next_line_utils.c

SOURCE_B = 

SRC_M = $(addprefix $(DIR_M)/, $(SOURCE_M)) tests/main.c

SRC_GNL = $(addprefix $(DIR_GNL)/, $(SOURCE_GNL))

SRC_B = $(addprefix $(DIR_B)/, $(SOURCE_B))

OBJ_M = $(addprefix $(DIR_OBJ)/, $(SOURCE_M:.c=.o)) lib/main.o

OBJ_GNL = $(addprefix $(DIR_OBJ)/, $(SOURCE_GNL:.c=.o))

OBJ_B = $(addprefix $(DIR_OBJ)/, $(SOURCE_B:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_M) $(OBJ_GNL) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@$(ECHO) "$(GREEN)$(NAME) Compilation Complete!$(DEFAULT)"

$(OBJ_M): $(SRC_M)
	@$(ECHO) "$(RED)Mandatory objects outdated in so_long! Compiling again...$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $^
	@mv -f $(SOURCE_M:.c=.o) main.o $(DIR_OBJ)

$(OBJ_GNL): $(SRC_GNL)
	@$(ECHO) "$(RED)Objects outdated in get_next_line! Compiling again...$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $^
	@mv -f $(SOURCE_GNL:.c=.o) $(DIR_OBJ)

bonus: $(OBJ_B) $(LIBFT) $(OBJ_GNL)
	@$(ECHO) "$(MAGENTA)Bonuses Compilation Complete in so_long!$(DEFAULT)"

$(OBJ_B): $(SRC_B)
	@$(ECHO) "$(RED)Bonus objects outdated in so_long! Compiling again...$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $^
	@mv -f $(SOURCE_B:.c=.o) $(DIR_OBJ)

$(LIBFT):
	@make all -C libft
	@cp libft/$(LIBFT) $(LIBFT)

test: all
	@$(ECHO) "Command: ./$(NAME) $(MAP)"
	@./$(NAME) $(MAP)

clean:
	@$(ECHO) "$(BLUE)Cleaning up object files in so_long...$(DEFAULT)"
	@make clean -C libft
	@$(RM) $(OBJ_M) $(OBJ_B) $(OBJ_GNL)

fclean: clean
	@$(RM) $(LIBFT)
	@$(RM) libft/$(LIBFT)
	@$(RM) $(NAME)
	@$(ECHO) "$(CYAN)Removed $(NAME)$(DEFAULT)"
	@$(ECHO) "$(CYAN)Removed $(LIBFT)$(DEFAULT)"

norminette:
	@$(ECHO) "$(CYAN)\nChecking norm for ft_printf...$(DEFAULT)"
	@norminette -R CheckForbiddenSourceHeader $(SRC_M) $(SRC_B) $(SRC_GNL) lib/
	@make norminette -C libft/

re: fclean all
	@$(ECHO) "$(YELLOW)Cleaned and Rebuilt Everything for $(NAME)!$(DEFAULT)"

git:
	git add ../.
	git commit
	git push

.PHONY: all clean fclean bonus norminette re