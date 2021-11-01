NAME := minishell 

#COLORS FOR FUN

RED := \033[0;31m
GREEN := \033[0;32m
BLUE := \033[0;34m
LBLUE := \033[1;34m
NC := \033[0m

#used folders

SDIR := src
IDIR := inc
ODIR := obj
DDIR := .debug
TDIR := tests

OS = $(shell uname)

#all the files

SRC = main.c \
	minishell.c \
	exit_shell.c \
	init_data.c \
	minishell_calloc.c \
	minishell_write.c \
	minishell_putchar_fd.c \
	minishell_putstr_fd.c \
	minishell_strdup.c \
	minishell_putendl_fd.c \
	increment_shlvl.c \
	built_in_functions/builtin_echo.c \
	built_in_functions/builtin_cd.c \
	built_in_functions/builtin_pwd.c \
	built_in_functions/builtin_export.c \
	built_in_functions/builtin_unset.c \
	built_in_functions/builtin_env.c \
	built_in_functions/builtin_exit.c \
	lexer/lexer.c \
	lexer/lexer_utils_1.c \
	lexer/lexer_utils_2.c \
	lexer/lexer_count_tokens.c \
	lexer/make_token_meta.c \
	lexer/make_token_quote.c \
	lexer/expand_variables.c \
	lexer/expand_utils_1.c \
	lexer/expand_utils_2.c \
	lexer/split_words.c \
	lexer/word_splitter.c \
	lexer/quote_removal.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/parse_pipeline.c \
	parser/parse_word_list.c \
	parser/parse_command.c \
	parser/parse_redirection.c \
	executor/execute.c \
	executor/execute_pipeline.c \
	executor/execute_command.c \
	executor/execute_word_list.c \
	executor/execute_builtin.c \
	executor/execute_here_doc.c \
	executor/execute_redirection.c \
	executor/execute_redirection_utils.c \
	executor/execute_utils.c \
	executor/search_command.c \
	executor/execute_free_child.c \
	executor/make_comand.c \
	environ/environ.c \
	environ/environ_utils.c \
	environ/environ_get_keyvalue.c \
	environ/environ_utils_2.c \
	signals/signals.c \
	Get-next-line/get_next_line.c \
	Get-next-line/get_next_line_utils.c

OBJ = $(addprefix $(ODIR)/$(SDIR)/, $(SRC:.c=.o))

LIBFT = libft
READLINE = -ltermcap -lreadline -L/usr/local/opt/readline/lib -L/Users/alkrusts/.brew/Cellar/readline/8.0.4/lib -L/Users/dkrecisz/.brew/Cellar/readline/8.1.1/lib
LIBS = -L $(LIBFT) -lft $(READLINE)

#headers aka dependencys

HEADER := -I $(IDIR) -I $(LIBFT) -I/Users/alkrusts/.brew/opt/readline/include -I/usr/local/opt/readline/include -I/Users/dkrecisz/.brew/Cellar/readline/8.1.1/include

DBG := $(patsubst %,$(DDIR)/%,$(OBJ))

#flags
 
C_DEBUG := -g -Wall -Werror -Wextra -fsanitize=address $(HEADER)
C_REGULAR := -Wall -Wextra -Werror -g $(HEADER)

CC := clang 

#if bonus

ifdef BONUS
	OBJ = 
else
	
endif

#id febug

ifdef DEBUG
	FLAGS = $(C_DEBUG)
else
	FLAGS = $(C_REGULAR)
endif

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "${GREEN}minishell ready!${NC}"

$(ODIR)/%.o: %.c
	@mkdir -p $(ODIR)/$(SDIR)/built_in_functions \
		$(ODIR)/$(SDIR)/lexer \
		$(ODIR)/$(SDIR)/parser \
		$(ODIR)/$(SDIR)/executor \
		$(ODIR)/$(SDIR)/environ \
		$(ODIR)/$(SDIR)/Get-next-line \
		$(ODIR)/$(SDIR)/signals
	@$(CC) $(FLAGS) $(HEADER) -c $< -o $@

$(LIBFT)/libft.a:
	@echo "${GREEN}Building libft${NC}"
	@make -C $(LIBFT)
	@echo "${GREEN}libft ready!${NC}"
	@echo "${GREEN}Building minishell${NC}"

clean:
	@echo "${RED}Cleaning build!${NC}"
	@rm -rf $(ODIR)
	@echo "${RED}Cleaning libft!${NC}"
	@make -C $(LIBFT) clean
#	@cd tests && bash test_all.sh --cleanup

fclean: clean
	@echo "${RED}Deleting minishell!${NC}"
	@rm -rf $(NAME)
	@echo "${RED}Deleting libft!${NC}"
	@make -C $(LIBFT) fclean

re: fclean all

run: all
	@./$(NAME)

test_expansions: all
	cd $(TDIR)/expansions && bash test_expansions.sh

test_environ: all
	cd $(TDIR)/environ && bash test_environ.sh

test_echo: all
	cd $(TDIR)/echo && bash test_echo.sh

test_all: all
#	cd tests && bash test_all.sh

valgrind: debug_1
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME)

debug: fclean
	@make DEBUG=1

.PHONY: all bonus clean fclean re run
