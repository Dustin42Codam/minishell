#!/bin/bash

# Path to root directory of minishell
MINISHELL_DIR="../.."

# Test input/output files
INPUT="test_expansions.in"
BASH_OUT="bash.out"
MINISHELL_OUT="minishell.out"
RESULTS="results.txt"

if [ "$1" == "--cleanup" ]; then
	rm -f $BASH_OUT
	rm -f $MINISHELL_OUT
	rm -f $RESULTS
	rm -f ./minishell
	exit 0
fi

# Build minishell and copy the executable into current directory
make -C $MINISHELL_DIR &>/dev/null
RET=$?
if [ $? -ne 0 ]; then
	echo "Error while building the project."
	exit $RET
fi
cp $MINISHELL_DIR/minishell .

# Create empty output files
echo > $BASH_OUT
echo > $MINISHELL_OUT

# Defining some test variables
export ARG_0="-n lol"
export ARG_1="lol"
export ARG_2=""
export ARG_3="$PWD"
export ARG_4="$PWD$HOME"
export ARG_5="$ARG_1"
export ARG_6="$ARG_1$ARG_2"
export ARG_7="$ARG_1$ARG_2abc"
export ARG_8="$ARG_1$ARG_2-$ARG_3"
export ARG_9="$ARG_1$ARG_2-$ARG_3,.-$ARG_8"
export ARG_10="$ARG_9$ARG_9$ARG_4$ARG_1"
export ARG_11="echo abc"

# Read input file and use each single line as an argument for 'echo'
while IFS= read -r line
do
	bash -c "echo $line" >> $BASH_OUT
	./minishell -c "echo $line" >> $MINISHELL_OUT
done < "$INPUT"

# Check differences
diff $BASH_OUT $MINISHELL_OUT > $RESULTS
RET=$?

if [ $RET -ne 0 ]; then
	echo "KO"
	cat $RESULTS
else
	echo "SUCCESS"
fi

exit $RET
