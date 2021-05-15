# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dkrecisz <dkrecisz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/15 20:22:43 by dkrecisz      #+#    #+#                  #
#    Updated: 2021/05/15 20:29:29 by dkrecisz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c
	  
OBJ = $(SRC:.c=.o)

# Specifying source + object directories
SRCDIR = src
OBJDIR = obj

# Adding directory prefixes to src filenames (minishell.c -> src/minishell.c)
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

LIBFT = libft

LIBS = -L $(LIBFT) -lft

HEADER = -I includes -I $(LIBFT)

CC = clang

CFLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean re run

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT)
	@$(CC) $(OBJS) $(HEADER) $(LIBS) -o $@
	@echo "[minishell is ready!]"

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT) clean
	@echo "[cleaned up object files.]"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "[everything cleaned up]"

re: fclean all

run: all
	@./$(NAME)
