# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 16:44:37 by aperez-b          #+#    #+#              #
#    Updated: 2021/08/06 21:42:19 by aperez-b         ###   ########.fr        #
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
GRATE = GAME_RATE=2000
ARATE = ANIM_RATE=700
GAME = game_mac.c
LMLX = -lmlx -framework OpenGL -framework AppKit
LMLX_PATH=/usr/lib
IMLX_PATH=/usr/include
ifeq ($(UNAME), Linux)
	ECHO = echo -e
	LEAKS = #valgrind --leak-check=full --show-leak-kinds=all -s -q 
	LMLX = -L$(LMLX_PATH) -lmlx -lXext -lX11
	IMLX = -I$(IMLX_PATH)
	GRATE = GAME_RATE=10000
	ARATE = ANIM_RATE=4500
	GAME = game_linux.c
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

CFLAGS = #-Wall -Wextra -Werror
RM = rm -f
CC = gcc
DIR_M = mandatory
DIR_GNL = get_next_line
DIR_B = bonus
DIR_OBJ = lib
LIBFT = libft/libft.a
NAME = so_long

KEYCODES =  -D $(ESC) -D $(Q) -D $(R) -D $(W) -D $(A) -D $(S) -D $(D) -D $(UP) -D $(DOWN) -D $(LEFT) -D $(RIGHT)

RATES = -D $(GRATE) -D $(ARATE)

SRC_MAPS1 = min.ber test.ber ghosts.ber multipac.ber medium.ber	\
		   google.ber run.ber classic.ber

SRC_MAPS2 = 20Hunt.ber bigHunt.ber capsuleClassic.ber			\
			classic.ber contestClassic.ber labAA1.ber			\
			labAA2.ber labAA3.ber labAA4.ber labAA5.ber			\
			mediumClassic.ber mimapa.ber minimaxClassic.ber		\
			newmap.ber oneHunt.ber openClassic.ber				\
			openHunt.ber originalClassic.ber ourLayout.ber		\
			sixHunt.ber smallClassic.ber smallHunt.ber			\
			testClassic.ber trappedClassic.ber trickyClassic.ber

MAPS1 = $(addprefix tests/, $(SRC_MAPS1))

MAPS2 = $(addprefix tests/other-maps/, $(SRC_MAPS2))

SOURCE_M = map.c player.c check.c $(GAME) sprites.c	\
		   utils.c anim.c render.c playerlist.c		\
		   ghosts.c pacman.c chase.c legal.c

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
	@$(CC) $(CFLAGS) $(CDEBUG) $(KEYCODES) $(RATES) -c $^
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

play: all
	@for map in $(MAPS1) ; do \
		$(ECHO) ; \
		$(ECHO) "Command: $(GRAY)$(LEAKS)./$(NAME) $$map$(DEFAULT)" ; \
		$(LEAKS) ./$(NAME) $$map ; \
	done

play2: all
	@for map in $(MAPS2) ; do \
		$(ECHO) ; \
		$(ECHO) "Command: $(GRAY)$(LEAKS)./$(NAME) $$map$(DEFAULT)" ; \
		$(LEAKS) ./$(NAME) $$map ; \
	done

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

.PHONY: all clean fclean bonus compile_libft norminette test play git re
