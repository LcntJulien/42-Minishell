# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:00:26 by jlecorne          #+#    #+#              #
#    Updated: 2025/01/22 03:51:08 by jlecorne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRAY 		= \033[90m
GREEN   	= \033[32m
RED			= \033[31m
MAGENTA 	= \033[35m
YELLOW  	= \033[33m
BLUE		= \033[34m
BOLD		= \033[1m
RESET   	= \033[0m

NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-ggdb3 #-> Utiliser avec Valgrind
SRCDIR		= srcs
SRC			= $(shell find $(SRCDIR) -name '*.c')
# SRC 		= $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c)
OBJDIR		= .obj
OBJ 		= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
HEADER		= -I include -I /opt/homebrew/opt/readline/include
LIBS 		= -lreadline -L /opt/homebrew/opt/readline/lib
LIBFT		= libft/libft.a

all: $(NAME)

$(LIBFT)	:
	$(MAKE) -sC libft

# Linking des objets et libs
$(NAME): $(LIBFT) $(OBJ)
	@printf "$(GRAY) - $(NAME)$(RESET)\t"
	@$(CC) $(CFLAGS) $(HEADER) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@printf "$(GREEN)[OK]$(RESET)\n"

# Compilation des sources et gestion de fichiers d'objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

# Suppression objets libft
clib:
	@$(MAKE) clean -sC libft

# Suppression programme libft
fclib:
	@$(MAKE) fclean -sC libft

# Suppression objets
clean: clib
	@if [ -d "$(OBJDIR)" ]; then \
		printf "$(GRAY) - $(NAME)$(RESET)\t"; \
		rm -rf $(OBJDIR); \
		printf "$(BLUE)[OBJECTS REMOVED]$(RESET)\n"; \
	else \
		printf "$(GRAY) - $(NAME)$(RESET)\t$(YELLOW)[NO OBJECTS FOUND]$(RESET)\n"; \
	fi

# Suppression programme
fclean: clean fclib
	@if [ -e "$(NAME)" ]; then \
		printf "$(GRAY) - $(NAME)$(RESET)\t"; \
		rm -f $(NAME); \
		printf "$(BLUE)[PROGRAM REMOVED]$(RESET)\n"; \
	else \
		printf "$(GRAY) - $(NAME)$(RESET)\t$(YELLOW)[NO FILE FOUND]$(RESET)\n"; \
	fi

re: fclean all

# Linking debug
debug: $(LIBFT) $(OBJ)
	@printf "$(GRAY) - $(NAME)$(RESET)\t"
	@$(CC) -g3 $(CFLAGS) $(HEADER) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME) -fsanitize=address
	@printf "$(BOLD)$(MAGENTA)[DEBUG]$(RESET)\n"

.PHONY: all, clib, fclib, clean, fclean, re, debug