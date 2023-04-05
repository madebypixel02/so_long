# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 16:44:37 by aperez-b          #+#    #+#              #
#    Updated: 2023/04/05 14:43:41 by aperez-b         ###   ########.fr        #
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
PRINTF = printf
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = gcc -MD
AR = ar rcs
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
OBJ_GNL_DIR = obj_gnl
BIN = so_long
NAME = $(BIN_DIR)/$(BIN)
LIBFT = libft/bin/libft.a
LIBFT_DIR = libft
LIBFT_SRC = $(shell [ -d libft ] && ls libft/src*/*.c)
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

$(NAME): $(LIBFT) $(OBJ) $(OBJ_GNL) | $(BIN_DIR)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJ) $(OBJ_GNL) $(LIBFT) $(LMLX) -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)$(BIN) is up to date!$(DEFAULT)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(GNL_DIR)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) $(CDEBUG) $(KEYCODES) $(RATES) -c $< -o $@

$(OBJ_GNL_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_GNL_DIR)
	@$(eval SRC_GNL_COUNT = $(shell expr $(SRC_GNL_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(MAGENTA)$<$(DEFAULT)..." "" $(SRC_GNL_COUNT) $(SRC_GNL_COUNT_TOT) $(SRC_GNL_PCT)
	@$(CC) $(CFLAGS) $(CDEBUG) $(KEYCODES) $(RATES) -c $< -o $@

bonus: all

$(LIBFT): $(LIBFT_SRC) | $(LIBFT_DIR) $(BIN_DIR)
	@make all -C libft
	@$(AR) $(NAME) $@

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

clean: | $(LIBFT_DIR)
	@$(PRINTF) "$(CYAN)Cleaning up object files in $(BIN)...$(DEFAULT)\n"
	@make clean -C libft
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_GNL_DIR)

fclean: clean | $(LIBFT_DIR)
	@$(RM) $(LIBFT)
	@$(PRINTF) "$(CYAN)Removed $(LIBFT)$(DEFAULT)\n"
	@$(RM) -r $(BIN_DIR)
	@$(PRINTF) "$(CYAN)Removed $(NAME)$(DEFAULT)\n"

norminette: | $(LIBFT_DIR) $(GNL_DIR)
	@make norminette -C libft
	@$(PRINTF) "$(CYAN)\nChecking norm for get_next_line...$(DEFAULT)\n"
	@norminette -R CheckForbiddenSourceHeader $(GNL_DIR)
	@$(PRINTF) "$(CYAN)\nChecking norm for $(BIN)...$(DEFAULT)\n"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) inc/

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_GNL_DIR):
	@mkdir -p $(OBJ_GNL_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(LIBFT_DIR):
	@git clone https://gitlab.com/madebypixel02/libft.git

$(GNL_DIR):
	@git clone https://gitlab.com/madebypixel02/get_next_line.git

re: fclean
	@make all

git:
	git add .
	git commit
	git push

-include $(OBJ_DIR)/*.d
-include $(OBJ_GNL_DIR)/*.d

.PHONY: all clean fclean bonus norminette test play git re
