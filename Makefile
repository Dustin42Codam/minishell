NAME := minishell 

#COLORS FOR FUN

RED := \033[0;31m
GREEN := \033[0;32m
BLUE := \033[0;34m
LBLUE := \033[1;34m
NC := \033[0m

#used folders

SDIR := src
IDIR := inc/
ODIR := $(SDIR)/.obj
DDIR := .debug

OS = $(shell uname)

#all the files

OBJ = main.o \
	test.o
#	ft_strcpy.o

#headers aka dependencys

HEADER := minishell.h

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

OBJ := $(patsubst %,$(ODIR)/%,$(OBJ))
DBG := $(patsubst %,$(DDIR)/%,$(OBJ))
INC := $(patsubst %,$(IDIR)/%,$(HEADER))

#flags

C_DEBUG := -g -Wall -Werror -Wextra -fsanitize=address -I$(IDIR)
C_REGULAR := -Wall -Werror -Wextra -I$(IDIR)

#nasm compiler

CC := gcc 

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

#libft
LIBFT = libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBS)
	@echo "${GREEN}Building minishell${NC}"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c $(INC)
	@mkdir -p $(@D)
	@$(CC) -c $(FLAGS) -o $@ $<

clean:
	@echo "${RED}Cleaning build!${NC}"
	@echo "${RED}Cleaning libft!${NC}"
	@make -C libft clean
	@rm -rf $(ODIR) 

$(LIBFT):
	@echo "${GREEN}Building libft${NC}"
	@make -C libft

fclean: clean
	@echo "${RED}Deleting minishell!${NC}"
	@echo "${RED}Deleting libft!${NC}"
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all

test: $(NAME) $(OBJ)
	@echo "${BLUE}Building test cases!${NC}"

test_d: fclean
	@make DEBUG=1
	@echo "${LBLUE}Building debugable test cases!${NC}"

.PHONY: all bonus test test_d clean fclean re
