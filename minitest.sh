#!/bin/bash

# Test script for random shell commands 

# Colors
GREEN="\033[0;32m"
WHITE="\e[1;37m"
RED="\033[0;31m"
RESET="\033[0m"


# Path to root directory of minishell
MINISHELL_DIR="./"

# Test input/output files
INPUT="input"
BASH_LOG="bash.log"
BASH_TMP="bash.tmp"
MINI_LOG="mini.log"
MINI_TMP="mini.tmp"
RESULTS="results.txt"
LOG="log.out"

if [ "$1" == "--cleanup" ]; then
	rm -f 1 2 3 4 5 6
	rm -f $BASH_TMP
	rm -f $MINI_TMP
	rm -f $BASH_LOG
	rm -f $MINI_LOG
	rm -f $RESULTS
	rm -f $LOG
	rm -f "in"
	rm -f "out"
	rm -f ./minishell
	exit
fi

# Build minishell and copy the executable into current directory
make -C $MINISHELL_DIR &>/dev/null
RET=$?
if [ $RET -ne 0 ]; then
	echo "Error while building the project."
	exit $RET
fi
cp $MINISHELL_DIR/minishell . &>/dev/null

# Create empty output files
echo > $BASH_LOG
echo > $MINI_LOG
echo > $RESULTS
echo > "$LOG"

KO=0
OK=0
COUNT=0
SEGFAULT=0

# Manual tests - redirect output

# +++++++++++++++++ TEST 00 +++++++++++++++++
TEST_CMD="echo abc >"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi

# +++++++++++++++++ TEST 01 +++++++++++++++++
TEST_CMD="ls / | sort | head -3 >"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi

# +++++++++++++++++ TEST 02 +++++++++++++++++
TEST_CMD="< colors.txt sort | uniq -c | sort -r | head -3 >"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi

# +++++++++++++++++ TEST 03 +++++++++++++++++
TEST_CMD="wc -l < colors.txt >"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi

# +++++++++++++++++ TEST 04 +++++++++++++++++
TEST_CMD="wc -l > out < colors.txt"

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat out > $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat out > $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 05 +++++++++++++++++
TEST_CMD="cat > out < 1 < 2 < 3"

echo "1" > 1
echo "2" > 2
echo "3" > 3

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat out > $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat out > $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 06 +++++++++++++++++
TEST_CMD="cat > out < 1 < 2 < 3 > 4"

echo "1" > 1
echo "2" > 2
echo "3" > 3
rm -f 4 
rm -f out

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
cat 4 >> $MINI_LOG
cat out > $MINI_LOG
echo > $MINI_LOG

echo "1" > 1
echo "2" > 2
echo "3" > 3
rm -f 4 
rm -f out

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
cat 4 >> $BASH_LOG
cat out > $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 07 +++++++++++++++++
TEST_CMD="> 1 > 2 > 3"

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 08 +++++++++++++++++
TEST_CMD="< 1 < 2 < 3"

echo 1 > 1
echo 2 > 2
echo 3 > 3

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
echo > $MINI_LOG

echo 1 > 1
echo 2 > 2
echo 3 > 3

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 09 +++++++++++++++++
TEST_CMD="< 1 < 2 < 3 > 4"

echo 1 > 1
echo 2 > 2
echo 3 > 3
echo 4 > 4

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
cat 4 >> $MINI_LOG
echo > $MINI_LOG

echo 1 > 1
echo 2 > 2
echo 3 > 3
echo 4 > 4

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
cat 4 >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 10 +++++++++++++++++
TEST_CMD="< 1 < 2 < 3 > 4 < 5"

echo 1 > 1
echo 2 > 2
echo 3 > 3
rm -f 4
echo 5 > 5

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
cat 4 >> $MINI_LOG
cat 5 >> $MINI_LOG
echo > $MINI_LOG

echo 1 > 1
echo 2 > 2
echo 3 > 3
rm -f 4
echo 5 > 5

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
cat 4 >> $BASH_LOG
cat 5 >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 11 +++++++++++++++++
TEST_CMD="cat < 1 < 2 < 3 > 4 < 5 > 6"

echo 1 > 1
echo 2 > 2
echo 3 > 3
rm -f 4
echo 5 > 5

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
cat 4 >> $MINI_LOG
cat 5 >> $MINI_LOG
cat 6 >> $MINI_LOG
echo > $MINI_LOG

echo 1 > 1
echo 2 > 2
echo 3 > 3
rm -f 4
echo 5 > 5

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
cat 4 >> $BASH_LOG
cat 5 >> $BASH_LOG
cat 6 >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 12 +++++++++++++++++
TEST_CMD="echo abc > 1 > 2 > 3"

rm -f 1 2 3 &>/dev/null

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
echo > $MINI_LOG

rm -f 1 2 3 &>/dev/null

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 13 +++++++++++++++++
TEST_CMD="cat < 1 < 2 < 42"

rm -f 42 &>/dev/null

echo 1 > 1
echo 2 > 2

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?

if [ $MINI_EXIT_CODE -ne 0 ]; then
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 14 +++++++++++++++++
TEST_CMD="cat > 1 > 2 < 3"

echo 1 > 1
echo 2 > 2
echo 3 > 3

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat 1 >> $MINI_LOG
cat 2 >> $MINI_LOG
cat 3 >> $MINI_LOG
echo > $MINI_LOG

echo 1 > 1
echo 2 > 2
echo 3 > 3

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat 1 >> $BASH_LOG
cat 2 >> $BASH_LOG
cat 3 >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 15 +++++++++++++++++
TEST_CMD="<"

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
echo > $BASH_LOG

if [ $MINI_EXIT_CODE -eq 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 16 +++++++++++++++++
TEST_CMD=">"

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
echo > $BASH_LOG

if [ $MINI_EXIT_CODE -eq 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 17 +++++++++++++++++
TEST_CMD=">>"

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
echo > $BASH_LOG

if [ $MINI_EXIT_CODE -eq 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 18 +++++++++++++++++
TEST_CMD="echo abc > > out"

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
echo > $MINI_LOG

if [ $MINI_EXIT_CODE -eq 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 19 +++++++++++++++++
TEST_CMD="cat >"

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
echo > $BASH_LOG

if [ $MINI_EXIT_CODE -eq 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 20 +++++++++++++++++
TEST_CMD="wc -l < in > out"

printf "1\n2\n3\n" > "in"
rm -f out

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat out > $MINI_LOG
echo > $MINI_LOG

rm -f out

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat out > $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 21 +++++++++++++++++
TEST_CMD="wc -l > out < in"

printf "1\n2\n3\n" > "in"
rm -f out

MINI_STDOUT=$(./minishell -c "${TEST_CMD}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat out > $MINI_LOG
echo > $MINI_LOG

rm -f out

BASH_STDOUT=$(bash -c "${TEST_CMD}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD}" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat out > $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD}${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD}${RESET}\n"
fi

# +++++++++++++++++ TEST 022 +++++++++++++++++

TEST_CMD="echo abc ||"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 023 +++++++++++++++++

TEST_CMD="< echo abc |"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 024 +++++++++++++++++

TEST_CMD=">|< echo abc |"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 025 +++++++++++++++++

TEST_CMD="              echo          | abc                             |                       <"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 026 +++++++++++++++++

TEST_CMD="||||||||||||||echo||||||||||||abc|||||||||||||||||||||||||||||||||||||||||||||||||||||<"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 027 +++++++++++++++++

TEST_CMD=">>>>>>>>>>>>>>echo>>>>>>>>>>>>abc>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 028 +++++++++++++++++

TEST_CMD="<<<<<<<<<<<<<<echo<<<<<<<<<<<<abc<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 29 +++++++++++++++++

TEST_CMD="out <||   <echo  <|   abc                           "

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 30 +++++++++++++++++

TEST_CMD="echo -n | $ |         "

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 31 +++++++++++++++++

TEST_CMD="echo -n |  echo $PWD |     cat -n | head -20 | wc  | cat -n  "

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi


# +++++++++++++++++ TEST 31 +++++++++++++++++

TEST_CMD="echo -n |  echo $PWD |     cat -n | head -20 | wc  | cat -n  "

MINI_STDOUT=$(./minishell -c "${TEST_CMD} ${MINI_TMP}")
MINI_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $MINI_LOG
echo -e "stdout:\t\t\"${MINI_STDOUT}\"" >> $MINI_LOG
echo -e "exit code:\t$MINI_EXIT_CODE" >> $MINI_LOG
printf "file content:\n" >> $MINI_LOG
cat "$MINI_TMP" >> $MINI_LOG
echo > $MINI_LOG

BASH_STDOUT=$(bash -c "${TEST_CMD} ${BASH_TMP}")
BASH_EXIT_CODE=$?
echo -e "command:\t${TEST_CMD} out" >> $BASH_LOG
echo -e "stdout:\t\t\"${BASH_STDOUT}\"" >> $BASH_LOG
echo -e "exit code:\t$BASH_EXIT_CODE" >> $BASH_LOG
printf "file content:\n" >> $BASH_LOG
cat "$BASH_TMP" >> $BASH_LOG
echo > $BASH_LOG

diff $BASH_LOG $MINI_LOG &>/dev/null
if [ $? -ne 0 ]; then
	printf "${RED}[KO]\t${WHITE}${TEST_CMD} out${RESET}\n"
else
	printf "${GREEN}[OK]\t${WHITE}${TEST_CMD} out${RESET}\n"
fi
