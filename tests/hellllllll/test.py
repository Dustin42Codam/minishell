import random
import os
"""
Creating a set of usable char comands
naturaly we can accese all the /bin
naturaly we can see availabe alias
naturaly we can run custom program

We have ; | < > << >>
"""


signals = ['^D', '^C', '^\\']

vailabe_comands = ["[", "df", "ln", "sh", "bash", "echo", "ls",
	"sleep", "cat", "ed", "mkdir", "stty", "chmod", "expr", "mv", "sync",
	"cp", "hostname", "pax", "tcsh,csh", "kill", "ps", "test", "dash", "ksh",
	"pwd", "unlink", "date", "launchctl", "rm", "wait4path", "dd", "link", "rmdir", "zsh"]

bin_vailabe_comands = ["/bin/[", "/bin/df", "/bin/ln", "/bin/sh", "/bin/bash", "/bin/echo",
	"/bin/ls", "/bin/sleep", "/bin/cat", "/bin/ed", "/bin/mkdir", "/bin/stty", "/bin/chmod",
	"/bin/expr", "/bin/mv", "/bin/sync", "/bin/cp", "/bin/hostname", "/bin/pax",
	"/bin/tcsh,csh", "/bin/kill", "/bin/ps", "/bin/test", "/bin/dash", "/bin/ksh", "/bin/pwd",
	"/bin/unlink", "/bin/date", "/bin/launchctl", "/bin/rm", "/bin/wait4path", "/bin/dd",
	"/bin/link", "/bin/rmdir", "/bin/zsh"]

bin_random = "./random_tests.out"

relative = ["../", "//", "~/", "/read_foler"]

len_of_valid_comands = len(vailabe_comands)

fout = open('comm.in', "a")

x = 0
line_cnt = 0

while (True):
	if (x == 0):
		line = input("how many lines of comands u want?\n")
		redirect = input("What redirection does u minishell take (sperated by spaces)? '>> | << >'\n")
		line_len = input("How amy comands per line\n")
		x = 1
		redirect = redirect.split()
		len_of_redirect = len(redirect)
		line = int(line)
	if (line == line_cnt):
		fout.close()
		os._exit(1)
	index_comand = random.randint(0, len_of_valid_comands - 1)
	index_redirect = random.randint(0, len_redirect - 1)
	comand = vailabe_comands[index_comand] + " " + redirect[redirect]
	fout.write(comand + "\n")
	line_cnt = line_cnt + 1
