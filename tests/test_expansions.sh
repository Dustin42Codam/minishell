#!/bin/bash

# Path to root directory of minishell
MINISHELL_DIR=".."

# Build minishell and copy the executable into current directory
make -C $MINISHELL_DIR &>/dev/null
RET=$?
if [ $? -ne 0 ]; then
	echo "Error while building the project."
	exit $RET
fi
cp $MINISHELL_DIR/minishell .

# printf "\n${BYEL}+%.18s${REDB} ${BHWHT}Testing variable expansions${RESET}${BYEL}%.18s+\n${RESET}" $div1 $div1

INPUT="test_expansions.in"
BASH_OUT="bash.out"
MINISHELL_OUT="minishell.out"
RESULTS="results.txt"

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
	# echo $line >> $BASH_OUT
	# echo $line >> $MINISHELL_OUT
	echo "echo $line" | bash >> $BASH_OUT
	echo "echo $line" | ./minishell >> $MINISHELL_OUT
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
