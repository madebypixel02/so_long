# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 16:44:37 by aperez-b          #+#    #+#              #
#    Updated: 2021/08/04 10:35:16 by aperez-b         ###   ########.fr        #
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

# Key Codes for MacOS
ESC = KEY_ESC=53
W = KEY_W=13
A = KEY_A=0
S = KEY_S=1
D = KEY_D=2
UP = KEY_UP=126
DOWN = KEY_DOWN=125
LEFT = KEY_LEFT=123
RIGHT = KEY_RIGHT=124
R = KEY_R=15
Q = KEY_Q=12

UNAME = $(shell uname -s)
ECHO = echo
CDEBUG = -g3 -fsanitize=address
LMLX = -lmlx -framework OpenGL -framework AppKit
LMLX_PATH=/usr/lib
IMLX_PATH=/usr/include
ifeq ($(UNAME), Linux)
	ECHO = echo -e
	LEAKS = valgrind --leak-check=full --show-leak-kinds=all -s -q 
	LMLX = -L$(LMLX_PATH) -lmlx -lXext -lX11
	IMLX = -I$(IMLX_PATH)
	# Key Codes for Linux
	ESC = KEY_ESC=65307
	W = KEY_W=119
	A = KEY_A=97
	S = KEY_S=115
	D = KEY_D=100
	UP = KEY_UP=65362
	DOWN = KEY_DOWN=65364
	LEFT = KEY_LEFT=65361
	RIGHT = KEY_RIGHT=65363
	R = KEY_R=114
	Q = KEY_Q=113

	CDEBUG =
endif

CFLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = gcc
DIR_M = mandatory
DIR_GNL = get_next_line
DIR_B = bonus
DIR_OBJ = lib
LIBFT = libft/libft.a
NAME = so_long
KEYCODES =  -D $(ESC) -D $(Q) -D $(R) -D $(W) -D $(A) -D $(S) -D $(D) -D $(UP) -D $(DOWN) -D $(LEFT) -D $(RIGHT)

SOURCE_M = map.c player.c check.c game.c sprites.c	\
		   utils.c anim.c render.c playerlist.c

SOURCE_GNL = get_next_line.c get_next_line_utils.c

SOURCE_B = 

SRC_M = $(addprefix $(DIR_M)/, $(SOURCE_M)) tests/main.c

SRC_GNL = $(addprefix $(DIR_GNL)/, $(SOURCE_GNL))

SRC_B = $(addprefix $(DIR_B)/, $(SOURCE_B))

OBJ_M = $(addprefix $(DIR_OBJ)/, $(SOURCE_M:.c=.o)) lib/main.o

OBJ_GNL = $(addprefix $(DIR_OBJ)/, $(SOURCE_GNL:.c=.o))

OBJ_B = $(addprefix $(DIR_OBJ)/, $(SOURCE_B:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_M) $(OBJ_GNL) compile_libft
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJ_M) $(OBJ_GNL) $(LIBFT) $(IMLX) $(LMLX) -o $@

$(OBJ_M): $(SRC_M)
	@$(ECHO) "$(RED)Mandatory objects outdated in so_long! Compiling again...$(DEFAULT)"
	@$(CC) $(CFLAGS) $(CDEBUG) $(KEYCODES) -c $^
	@mv -f $(SOURCE_M:.c=.o) main.o $(DIR_OBJ)
	@$(ECHO) "$(GREEN)Mandatory Compilation Complete in so_long!$(DEFAULT)"

$(OBJ_GNL): $(SRC_GNL)
	@$(ECHO) "$(RED)Objects outdated in get_next_line! Compiling again...$(DEFAULT)"
	@$(CC) $(CFLAGS) $(CDEBUG) -c $^
	@mv -f $(SOURCE_GNL:.c=.o) $(DIR_OBJ)
	@$(ECHO) "$(GREEN)get_next_line Compilation Complete!$(DEFAULT)"

bonus: $(OBJ_B) $(LIBFT) $(OBJ_GNL)

$(OBJ_B): $(SRC_B)
	@$(ECHO) "$(RED)Bonus objects outdated in so_long! Compiling again...$(DEFAULT)"
	@$(CC) $(CFLAGS) $(CDEBUG) -c $^
	@mv -f $(SOURCE_B:.c=.o) $(DIR_OBJ)
	@$(ECHO) "$(MAGENTA)Bonus Compilation Complete in so_long!$(DEFAULT)"

compile_libft:
	@make all -C libft/

test: all
	@$(ECHO) "$(YELLOW)Performing test with custom main...$(DEFAULT)"
	@$(ECHO)
	@$(ECHO) "Command: $(GRAY)$(LEAKS)./$(NAME) $(MAP)$(DEFAULT)"
	@$(ECHO)
	@$(LEAKS)./$(NAME) $(MAP)

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
	@$(ECHO) "$(CYAN)\nChecking norm for so_long...$(DEFAULT)"
	@norminette -R CheckForbiddenSourceHeader $(SRC_M) $(SRC_B) lib/
	@$(ECHO) "$(CYAN)\nChecking norm for get_next_line...$(DEFAULT)"
	@norminette -R CheckForbiddenSourceHeader $(SRC_GNL) $(DIR_GNL)/get_next_line.h
	@make norminette -C libft/

re: fclean all
	@$(ECHO) "$(YELLOW)Cleaned and Rebuilt Everything for $(NAME)!$(DEFAULT)"

git:
	git add .
	git commit
	git push

.PHONY: all clean fclean bonus compile_libft norminette test git re
