#!/bin/bash

# Colors
GREEN="\033[0;32m"
WHITE="\e[1;37m"
RED="\033[0;31m"
RESET="\033[0m"

TEST_ECHO="./echo"
TEST_ENVIRON="./environ"
TEST_EXPANSION="./expansions"

# Just clean up files and exit
if [ "$1" == "--cleanup" ]; then
	cd ./environ && bash test_environ.sh --cleanup &>/dev/null && cd ..
	cd ./expansions && bash test_expansions.sh --cleanup && cd ..
	cd ./echo && bash test_echo.sh --cleanup &>/dev/null && cd ..
	cd ./cd && bash test_cd.sh --cleanup &>/dev/null && cd ..
	exit 0
fi

printf "\n${WHITE}Testing environment functions...\n"
cd environ && bash test_environ.sh &>/dev/null 
RET_ENVIRON=$?
if [ $RET_ENVIRON -eq 0 ]; then
	printf "Result:\t${GREEN}[OK]!\n${RESET}"
else
	printf "Result:\t${RED}[KO]!\n${RESET}"
fi
cd ..

printf "\n${WHITE}Testing variable expansions...\n"
cd expansions && bash test_expansions.sh
RET_EXPANSION=$?
if [ $RET_EXPANSION -eq 0 ]; then
	printf "Result:\t${GREEN}[OK]!\n${RESET}"
else
	printf "Result:\t${RED}[KO]!\n${RESET}"
fi
cd ..

printf "\n${WHITE}Testing echo builtin...\n"
cd ./echo
bash test_echo.sh
RET_ECHO=$?
if [ $RET_ECHO -eq 0 ]; then
	printf "Result:\t${GREEN}[OK]!\n${RESET}"
else
	printf "Result:\t${RED}[KO]!\n${RESET}"
	exit $RET_ECHO
fi

printf "\n${WHITE}Testing cd builtin...\n"
cd ./cd
bash ./test_cd.sh
RET_CD=$?
if [ $RET_CD -eq 0 ]; then
	printf "Result:\t${GREEN}[OK]!\n${RESET}"
else
	printf "Result:\t${RED}[KO]!\n${RESET}"
	exit $RET_CD
fi
