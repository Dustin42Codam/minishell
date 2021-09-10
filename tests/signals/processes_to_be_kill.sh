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
echo "bash -3 "cat""

bash -c "cat"

bash_res=$?

sleep 0.1
echo "kill -3 pidof cat"
sleep 0.1
printf "bash exit code: ${WHITE} $bash_res ${RESET}"

if [ "$mini_res" == "$bash_res" ]; then
	COLOR=$GREEN
	TEST="[OK]"
else
	COLOR=$RED
	TEST="[KO]"
fi
printf "${COLOR}${TEST}${RESET}\n"
