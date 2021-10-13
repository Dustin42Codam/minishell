# Colors
GREEN="\033[0;32m"
WHITE="\e[1;37m"
RED="\033[0;31m"
RESET="\033[0m"
# COLORS

TEST=""
COLOR=""

#SRC
MINISHELL_DIR="../.."

make -C $MINISHELL_DIR &>/dev/null
RET=$?
if [ $? -ne 0 ]; then
	echo "Error while building the project."
	exit 1
fi

cp $MINISHELL_DIR/minishell .

#SIGINT

printf "TESTING ${WHITE} SIGINT ${RESET}\n"

echo "./minishell -c "cat""

./minishell -c "cat"

mini_res=$?

echo "kill -2 pidof cat"
sleep 0.1
printf "minishell exit code: ${WHITE} $mini_res ${RESET}\n"
sleep 0.1
echo "bash -c "cat""

bash -c "cat"

bash_res=$?

sleep 0.1
echo "kill -2 pidof cat"
sleep 0.1
printf "bash exit code: ${WHITE} $bash_res ${RESET}\n"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"

#SIGQUIT

printf "TESTING ${WHITE} SIGQUIT ${RESET}\n"

echo "./minishell -c "cat""

./minishell -c "cat"

mini_res=$?

echo "kill -3 pidof cat"
sleep 0.1
printf "minishell exit code: ${WHITE} $mini_res ${RESET}\n"
sleep 0.1
echo "bash -c "cat""

bash -c "cat"

bash_res=$?

sleep 0.1
echo "kill -3 pidof cat"
sleep 0.1
printf "bash exit code: ${WHITE} $bash_res ${RESET}\n"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"

gcc no_premiss.c -o a.out
chmod 000 a.out

sleep 1 

printf "\nTESTING ${WHITE} EXIT CODES ${RESET}\n"

sleep 0.3
printf "."
sleep 0.3
printf "."
sleep 0.3
printf ".\n"


./minishell -c "a.out"
mini_res=$?

printf "minishell exit code: ${WHITE} $mini_res ${RESET}\n"

bash -c "a.out"
bash_res=$?

printf "bash exit code: ${WHITE} $bash_res ${RESET}\n"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"

./minishell -c "./aaaaaaaaaaaaaaaaaaaaaaaa"
mini_res=$?
printf "minishell exit code: ${WHITE} $mini_res ${RESET}\n"

bash -c "./aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
bash_res=$?
printf "bash exit code: ${WHITE} $bash_res ${RESET}\n"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"

printf "./minishell ls\n"
./minishell -c "ls"
mini_res=$?
printf "minishell exit code: ${WHITE} $mini_res ${RESET}\n"

printf "bash ls\n"
bash -c "ls"
bash_res=$?
printf "bash exit code: ${WHITE} $bash_res ${RESET}\n"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"

printf "./minishell exit -20\n"
./minishell -c "exit -20"
mini_res=$?
printf "minishell exit code: ${WHITE} $mini_res ${RESET}\n"

printf "bash exit -20\n"
bash -c "exit -20"
bash_res=$?
printf "bash exit code: ${WHITE} $bash_res ${RESET}\n"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"

printf "./minishell cd asdfjon\n"
./minishell -c "./minishell cd asdfjon"
mini_res=$?
printf "minishell exit code: ${WHITE} $mini_res ${RESET}\n"

printf "bash cd asdfjon\n"
bash -c "cd asdfjon"
bash_res=$?
printf "bash exit code: ${WHITE} $bash_res ${RESET}\n"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"

rm -rf a.out
rm minishell
