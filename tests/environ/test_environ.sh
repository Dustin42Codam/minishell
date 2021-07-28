#!/bin/bash

# Path to root directory of minishell
MINISHELL_DIR="../.."

# Test input/output files
TEST_SRC="test_environ.c"
TEST_OUT="test_environ.out"
VALGRIND_OUT="valgrind.out"

# Just clean up files and exit
if [ "$1" == "--cleanup" ]; then
	rm -f $TEST_OUT
	rm -f $VALGRIND_OUT
	rm -f ./minishell
	make fclean -C $MINISHELL_DIR
	exit 0
fi

# Build minishell and copy the executable into current directory
make -C $MINISHELL_DIR &>/dev/null
RET=$?
if [ $? -ne 0 ]; then
	echo "Error while building the project."
	exit 1
fi
cp $MINISHELL_DIR/minishell .

# Compile test source and start executable
gcc -g test_environ.c \
	$MINISHELL_DIR/src/environ.c \
	$MINISHELL_DIR/src/environ_utils.c \
	$MINISHELL_DIR/src/secure_calloc.c \
	$MINISHELL_DIR/src/exit_shell.c \
	$MINISHELL_DIR/libft/libft.a \
	-I $MINISHELL_DIR/inc \
	-I $MINISHELL_DIR/libft \
	-o $TEST_OUT

RET=$?
if [ $? -ne 0 ]; then
	echo "Error while building the test."
	exit 1
fi
./$TEST_OUT
TEST_RET=$?

if [ $TEST_RET -ne 0 ]; then
	echo "Test exited with code [$TEST_RET]!"
elif [ $TEST_RET -eq 0 ]; then
	echo "Test passed!"
fi

which valgrind &>/dev/null
if [ $? -eq 0 ]; then
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$TEST_OUT &> $VALGRIND_OUT
	cat $VALGRIND_OUT | grep -q "0 errors" && cat $VALGRIND_OUT | grep -q "no leaks are possible"
	VALGRIND_RET=$?

	if [ $VALGRIND_RET -ne 0 ]; then
		echo "Valgrind exited with code [$TEST_RET]!"
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$TEST_OUT
	elif [ $VALGRIND_RET -eq 0 ]; then
		echo "Valgrind couldn't find any leaks or errors!"
	fi
fi

exit $TEST_RET
