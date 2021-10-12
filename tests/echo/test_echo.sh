#!/bin/bash

# Test script for minishell echo builtin

# Colors
GREEN="\033[0;32m"
WHITE="\e[1;37m"
RED="\033[0;31m"
RESET="\033[0m"


# Path to root directory of minishell
MINISHELL_DIR="../.."

# Test input/output files
INPUT="echo.in"
BASH_OUT="bash.out"
MINISHELL_OUT="minishell.out"
RESULTS="results.txt"
LOG="log.out"

if [ "$1" == "--cleanup" ]; then
	rm -f $BASH_OUT
	rm -f $MINISHELL_OUT
	rm -f $RESULTS
	rm -f $LOG
	rm -f ./minishell
	exit
fi

# Build minishell and copy the executable into current directory
make -C $MINISHELL_DIR &>/dev/null
RET=$?
if [ $RET -ne 0 ]; then
	echo "Error while building the project."
	exit 1
fi
cp $MINISHELL_DIR/minishell .

# Create empty output files
echo > $BASH_OUT
echo > $MINISHELL_OUT
echo > $RESULTS
echo > "$LOG"

KO=0
OK=0
COUNT=0
SEGFAULT=0

# Read input file and pass each LINE as an argument to bash and minishell
while read -r LINE
do
	MINI_OUTPUT=$(./minishell -c $LINE)
	MINI_RET=$?
	while [ $MINI_RET -eq 139 ]
	do
		MINI_OUTPUT=$(./minishell -c $LINE)
		MINI_RET=$?
		((SEGFAULT+=1))
		if [ $SEGFAULT -ge 10 ]; then
			break
		fi
		sleep 0.03
	done
	echo "$MINI_OUTPUT" >> $MINISHELL_OUT

	BASH_OUTPUT=$(bash -c $LINE)
	BASH_RET=$?
	echo "$BASH_OUTPUT" >> $BASH_OUT

	if [ "$BASH_OUTPUT" == "$MINI_OUTPUT" ]; then
		COLOR=$GREEN
		TEST="[OK]"
		((OK+=1))
	else
		COLOR=$RED
		TEST="[KO]"
		((KO+=1))
	fi

	printf "${COLOR}${TEST}${RESET}\t${WHITE}%s${RESET}\n" "$LINE"
	if [ "$TEST" = "[KO]" ]; then
		printf "${WHITE}bash:\t\t["$BASH_OUTPUT"]\nminishell:\t["$MINI_OUTPUT"]\n${RESET}\n"

		echo -e "Command:\t${LINE}" >> "$LOG"
		printf "bash:\t\t[${BASH_OUTPUT}]\nminishell:\t[${MINI_OUTPUT}]\n\n" >> "$LOG"
	fi

	sleep 0.03
	((COUNT+=1))
done < $INPUT

diff $BASH_OUT $MINISHELL_OUT
if [ $? -ne 0 ]; then
	((KO+=1))
fi

if [ $KO -eq 0 ]; then
	echo "Passed all the test cases!" > "$LOG"
fi

printf "Results:\n"
printf "${KO} KOs\n"
printf "${OK} OKs\n"

exit $KO
