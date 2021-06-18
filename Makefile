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

SRC = main.c exit_shell.c init_data.c read_line.c \
	tokenizer.c tokenizer_utils_1.c tokenizer_utils_2.c tokenizer_utils_3.c \
	token_debug.c \
	parse_astree.c astree_utils.c \
	parse_command_line.c parse_job.c parse_command.c parse_simple_command.c \
	execute.c execute_utils.c



TEST =

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(SDIR)/, $(SRC))
OBJS = $(addprefix $(ODIR)/, $(OBJ))
TESTS = $(addprefix $(TDIR)/, $(TEST))

LIBFT = libft

LIBS = -L $(LIBFT) -lft

#headers aka dependencys

HEADER := -I $(IDIR) -I $(LIBFT)

#check what os we are one 

#ifeq ($(OS), Linux)
#	NASM_FLAGS := -felf64 -I$(IDIR)
#	#need to change this
#	LIB := -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
#else
#	NASM_FLAGS := -fmacho64 -I$(IDIR)
#	LIB := -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
#endif

# set paths

# OBJ := $(patsubst %,$(ODIR)/%,$(OBJ))
DBG := $(patsubst %,$(DDIR)/%,$(OBJ))

#flags

C_DEBUG := -g -Wall -Werror -Wextra -fsanitize=address $(HEADER)
C_DEBUG_1 := -g $(HEADER) -D DEBUG_1=1
C_DEBUG_2 := -g -Wall -Werror -Wextra $(HEADER) -D DEBUG_2=1
C_REGULAR := -Wall -Werror -Wextra $(HEADER)

#nasm compiler

CC := clang 

#if bonus

ifdef BONUS
	OBJ = 
else
	
endif

#id febug

ifeq ($(DEBUG), 1)
	FLAGS = $(C_DEBUG)
else ifeq ($(DEBUG_1), 1)
	FLAGS = $(C_DEBUG_1)
else ifeq ($(DEBUG_2), 1)
	FLAGS = $(C_DEBUG_2)
else
	FLAGS = $(C_REGULAR)
endif

all: $(NAME)

$(NAME): $(LIBFT)/libft.a $(OBJS)
	@echo "${GREEN}Building minishell${NC}"
	@$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "${GREEN}minishell ready!${NC}"

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(ODIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT)/libft.a:
	@echo "${GREEN}Building libft${NC}"
	@make -C $(LIBFT)
	@echo "${GREEN}libft ready!${NC}"

clean:
	@echo "${RED}Cleaning build!${NC}"
	@rm -rf $(ODIR)
	@echo "${RED}Cleaning libft!${NC}"
	@make -C $(LIBFT) clean

fclean: clean
	@echo "${RED}Deleting minishell!${NC}"
	@rm -rf $(NAME)
	@echo "${RED}Deleting libft!${NC}"
	@make -C $(LIBFT) fclean

re: fclean all

run: all
	@./$(NAME)

test: $(OBJS) $(LIBFT)/libft.a
	@echo "${BLUE}No test cases to build!${NC}"

debug: fclean
	@make DEBUG=1

debug_1: fclean
	@make DEBUG_1=1

debug_2: fclean
	@make DEBUG_2=1

valgrind: debug_1
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all bonus test test_d clean fclean re run
