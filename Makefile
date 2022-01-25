# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 16:44:37 by aperez-b          #+#    #+#              #
#    Updated: 2022/01/25 16:12:36 by aperez-b         ###   ########.fr        #
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

SHELL=/bin/bash
UNAME = $(shell uname -s)

# Properties for MacOS
CDEBUG = #-g3 -fsanitize=address
GRATE = GAME_RATE=17
GAME = game_mac.c
RENDER = render_mac.c
LMLX = -lmlx -framework OpenGL -framework AppKit
ifeq ($(UNAME), Linux)
	#Properties for Linux
	LEAKS =  valgrind --leak-check=full --show-leak-kinds=all -s -q 
	LMLX = -lmlx -lXext -lX11
	GAME = game_linux.c
	RENDER = render_linux.c
	GRATE = GAME_RATE=80
	CDEBUG =

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
endif

# Make variables
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = gcc -MD
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
OBJ_GNL_DIR = obj_gnl
BIN = so_long
NAME = $(BIN_DIR)/$(BIN)
PRINTF = LC_NUMERIC="en_US.UTF-8" printf
LIBFT = libft/bin/libft.a
GNL_DIR = get_next_line

# Keycodes defined during compilation
KEYCODES =  -D $(ESC) -D $(Q) -D $(R) -D $(W) -D $(A) -D $(S) -D $(D) -D $(UP) -D $(DOWN) -D $(LEFT) -D $(RIGHT)

# Game speeds defined during compilation
RATES = -D $(GRATE)

# Batch of basic playable maps
SRC_MAPS1 = min.ber test.ber ghosts.ber multipac.ber medium.ber	\
		   google.ber island.ber run.ber classic.ber

# Batch of experimental maps (from Machine-Learning-Pacman python project)
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

SRC = map.c player.c check.c $(GAME) sprites.c		\
		   utils.c anim.c $(RENDER) playerlist.c	\
		   ghosts.c pacman.c chase.c legal.c		\
		   score.c load_dir.c anim_dir.c main.c

SRC_GNL = get_next_line.c get_next_line_utils.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_GNL = $(addprefix $(OBJ_GNL_DIR)/, $(SRC_GNL:.c=.o))

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
	SRC_COUNT_TOT := $(shell echo -n $(SRC) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))
SRC_GNL_COUNT_TOT := $(shell expr $(shell echo -n $(SRC_GNL) | wc -w) - $(shell ls -l $(OBJ_GNL_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_GNL_COUNT_TOT) -le 0; echo $$?),0)
	SRC_GNL_COUNT_TOT := $(shell echo -n $(SRC_GNL) | wc -w)
endif
SRC_GNL_COUNT := 0
SRC_GNL_PCT = $(shell expr 100 \* $(SRC_GNL_COUNT) / $(SRC_GNL_COUNT_TOT))

all: $(NAME)

$(NAME): create_dirs compile_libft $(OBJ_GNL) $(OBJ)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJ) $(OBJ_GNL) $(LIBFT) $(LMLX) -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)$(BIN) is up to date!$(DEFAULT)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) $(CDEBUG) $(KEYCODES) $(RATES) -c $< -o $@

$(OBJ_GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@$(eval SRC_GNL_COUNT = $(shell expr $(SRC_GNL_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_GNL_COUNT) $(SRC_GNL_COUNT_TOT) $(SRC_GNL_PCT)
	@$(CC) $(CFLAGS) $(CDEBUG) $(KEYCODES) $(RATES) -c $< -o $@

bonus: all

compile_libft:
	@if [ ! -d "get_next_line" ]; then \
		git clone https://github.com/madebypixel02/get_next_line.git; \
	fi
	@if [ ! -d "libft" ]; then \
		git clone https://github.com/madebypixel02/libft.git; \
	fi
	@make all -C libft/

create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_GNL_DIR)
	@mkdir -p $(BIN_DIR)

test: all
	@$(PRINTF) "$(YELLOW)Performing test with custom map...$(DEFAULT)\n\n"
	@$(PRINTF) "Command: $(GRAY)$(LEAKS)./$(NAME) $(MAP)$(DEFAULT)\n\n"
	@$(LEAKS)./$(NAME) $(MAP)

play: all
	@for map in $(MAPS1) ; do \
		$(PRINTF) "\nCommand: $(GRAY)$(LEAKS)./$(NAME) $$map$(DEFAULT)\n" ; \
		$(LEAKS) ./$(NAME) $$map ; \
	done

play2: all
	@for map in $(MAPS2) ; do \
		$(PRINTF) "\nCommand: $(GRAY)$(LEAKS)./$(NAME) $$map$(DEFAULT)\n" ; \
		$(LEAKS) ./$(NAME) $$map ; \
	done

clean:
	@$(PRINTF) "$(CYAN)Cleaning up object files in $(BIN)...$(DEFAULT)\n"
	@if [ -d "libft" ]; then \
		make clean -C libft; \
	fi
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_GNL_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@if [ -d "libft" ]; then \
		$(RM) $(LIBFT); \
	fi
	@$(PRINTF) "$(CYAN)Removed $(NAME)$(DEFAULT)\n"
	@if [ -d "libft" ]; then \
		$(PRINTF) "$(CYAN)Removed $(LIBFT)$(DEFAULT)\n"; \
	fi

norminette:
	@if [ -d "libft" ]; then \
		make norminette -C libft/; \
	fi
	@if [ -d "get_next_line" ]; then \
		$(PRINTF) "$(CYAN)\nChecking norm for get_next_line...$(DEFAULT)\n"; \
		norminette -R CheckForbiddenSourceHeader $(GNL_DIR); \
	fi
	@$(PRINTF) "$(CYAN)\nChecking norm for $(BIN)...$(DEFAULT)\n"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) inc/

re: fclean
	@make all

git:
	git add .
	git commit
	git push

-include $(OBJ_DIR)/*.d
-include $(OBJ_GNL_DIR)/*.d

.PHONY: all clean fclean bonus compile_libft norminette test play create_dirs git re
