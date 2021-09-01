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
	minishell_putendl_fd.c \
	increment_shlvl.c \
	built_in_functions/builtin_echo.c \
	built_in_functions/builtin_cd.c \
	built_in_functions/builtin_pwd.c \
	built_in_functions/builtin_export.c \
	built_in_functions/builtin_unset.c \
	built_in_functions/builtin_env.c \
	built_in_functions/builtin_exit.c \
	terminal_capabilities/termcap_functions_calling_termcap_database_2.c \
	terminal_capabilities/termcap_is_functions_2.c \
	terminal_capabilities/termcap_get_functions_2.c \
	terminal_capabilities/termcap_print_functions_2.c \
	terminal_capabilities/termcap_DLL_history_2.c \
	terminal_capabilities/termcap_functions_calling_termcap_database_3.c \
	terminal_capabilities/termcap_is_functions_3.c \
	terminal_capabilities/termcap_get_functions_3.c \
	terminal_capabilities/termcap_unsed.c \
	terminal_capabilities/termcap_DLL_input_line_4.c \
	terminal_capabilities/termcap_is_functions_4.c \
	terminal_capabilities/termcap_get_functions_4.c \
	terminal_capabilities/termcap_get_functions_5.c \
	terminal_capabilities/termcap_read.c \
	terminal_capabilities/termcap_DLL_input_line_new_node.c \
	terminal_capabilities/termcap_DLL_history_new_node.c \
	terminal_capabilities/termcap_DLL_input_line_free.c \
	terminal_capabilities/termcap_DLL_history_free.c \
	terminal_capabilities/termcap_0_read_line.c \
	terminal_capabilities/termcap_functions_calling_termcap_database.c \
	terminal_capabilities/termcap_DLL_history_update.c \
	terminal_capabilities/termcap_write.c \
	terminal_capabilities/termcap_is_functions_keys_size.c \
	terminal_capabilities/termcap_DLL_input_pop.c \
	terminal_capabilities/termcap_del_char.c \
	terminal_capabilities/termcap_history_behaviur.c \
	terminal_capabilities/termcap_utils.c \
	terminal_capabilities/termcap_free_functions.c \
	terminal_capabilities/termcap_get_functions.c \
	terminal_capabilities/termcap_init_functions.c \
	terminal_capabilities/termcap_print_functions.c \
	terminal_capabilities/termcap_is_functions_keys.c \
	terminal_capabilities/termcap_DLL_input_line_get.c \
	terminal_capabilities/termcap_move_cursor_left.c \
	terminal_capabilities/termcap_move_cursor_right.c \
	terminal_capabilities/termcap_DLL_input_insert.c \
	terminal_capabilities/termcap_DLL_history_insert.c \
	terminal_capabilities/termcap_DLL_history_copy.c \
	lexer/lexer.c \
	lexer/lexer_utils_1.c \
	lexer/lexer_utils_2.c \
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
	executor/execute_utils.c \
	executor/search_command.c \
	environ/environ.c \
	environ/environ_utils.c \
	signals/signals_call_function_by_sig.c \
	signals/signals_init_sig.c \
	signals/signals.c

OBJ = $(addprefix $(ODIR)/$(SDIR)/, $(SRC:.c=.o))

#SRCS = $(addprefix $(SDIR)/, $(SRC))
#OBJS = $(addprefix $(ODIR)/, $(OBJ))
#TESTS = $(addprefix $(TDIR)/, $(TEST))

LIBFT = libft
TERMCAPS = -ltermcap
LIBS = -L $(LIBFT) -lft $(TERMCAPS) -lreadline

#headers aka dependencys

HEADER := -I $(IDIR) -I $(LIBFT)

# OBJ := $(patsubst %,$(ODIR)/%,$(OBJ))
DBG := $(patsubst %,$(DDIR)/%,$(OBJ))

#flags

C_DEBUG := -g -Wall -Werror -Wextra -fsanitize=address $(HEADER)
# C_REGULAR := -Wall -Wextra -Werror -g $(HEADER)
C_REGULAR := -Wall -Wextra -g $(HEADER)

#nasm compiler

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
	@echo "${GREEN}Building minishell${NC}"
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "${GREEN}minishell ready!${NC}"

$(ODIR)/%.o: %.c
	@mkdir -p $(ODIR)/$(SDIR)/built_in_functions \
		$(ODIR)/$(SDIR)/terminal_capabilities \
		$(ODIR)/$(SDIR)/lexer \
		$(ODIR)/$(SDIR)/parser \
		$(ODIR)/$(SDIR)/executor \
		$(ODIR)/$(SDIR)/environ \
		$(ODIR)/$(SDIR)/signals
	@$(CC) $(FLAGS) $(HEADER) -c $< -o $@

$(LIBFT)/libft.a:
	@echo "${GREEN}Building libft${NC}"
	@make -C $(LIBFT)
	@echo "${GREEN}libft ready!${NC}"

clean:
	@echo "${RED}Cleaning build!${NC}"
	@rm -rf $(ODIR)
	@echo "${RED}Cleaning libft!${NC}"
	@make -C $(LIBFT) clean
	@cd tests && bash test_all.sh --cleanup

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
	cd tests && bash test_all.sh

valgrind: debug_1
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME)

debug: fclean
	@make DEBUG=1

.PHONY: all bonus clean fclean re run
