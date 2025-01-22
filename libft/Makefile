# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 01:51:20 by jlecorne          #+#    #+#              #
#    Updated: 2025/01/22 04:03:04 by jlecorne         ###   ########.fr        #
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

NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-fsanitize=address #-> Debug
AR			= ar rc
SRCDIR		= srcs
SRC 		= $(wildcard $(SRCDIR)/*.c)
OBJDIR		= .obj
OBJ			= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
HEAD		= -I include

all: $(NAME)

$(NAME) : $(OBJ)
	@printf "$(GRAY) - $(NAME)$(RESET)\t"
	@$(AR) $(NAME) $(OBJ)
	@printf "$(GREEN)[OK]$(RESET)\n"

# Compilation des sources et gestion de fichiers d'objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

# Suppression objets
clean:
	@if [ -d "$(OBJDIR)" ]; then \
		printf "$(GRAY) - $(NAME)$(RESET)\t"; \
		rm -rf $(OBJDIR); \
		printf "$(BLUE)[OBJECTS REMOVED]$(RESET)\n"; \
	else \
		printf "$(GRAY) - $(NAME)$(RESET)\t$(YELLOW)[NO OBJECTS FOUND]$(RESET)\n"; \
	fi

# Suppression programme
fclean: clean
	@if [ -e "$(NAME)" ]; then \
		printf "$(GRAY) - $(NAME)$(RESET)\t"; \
		rm -f $(NAME); \
		printf "$(BLUE)[PROGRAM REMOVED]$(RESET)\n"; \
	else \
		printf "$(GRAY) - $(NAME)$(RESET)\t$(YELLOW)[NO FILE FOUND]$(RESET)\n"; \
	fi

re: fclean all

.PHONY: all, clean, fclean, re