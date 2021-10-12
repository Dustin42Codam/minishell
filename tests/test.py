import random
"""
Creating a set of usable char comands
naturaly we can accese all the /bin
naturaly we can see availabe alias
naturaly we can run custom program

We have ; | < > << >>
"""

pipes = [";", "|", "<", "<<", ">", ">>"]
vailabe_comands = ["[", "df", "ln", "sh", "bash", "echo", "ls", "sleep", "cat", "ed", "mkdir", "stty", "chmod", "expr", "mv", "sync", "cp", "hostname", "pax", "tcsh,csh", "kill", "ps", "test", "dash", "ksh", "pwd", "unlink", "date", "launchctl", "rm", "wait4path", "dd", "link", "rmdir", "zsh"]
bin_vailabe_comands = ["/bin/[", "/bin/df", "/bin/ln", "/bin/sh", "/bin/bash", "/bin/echo", "/bin/ls", "/bin/sleep", "/bin/cat", "/bin/ed", "/bin/mkdir", "/bin/stty", "/bin/chmod", "/bin/expr", "/bin/mv", "/bin/sync", "/bin/cp", "/bin/hostname", "/bin/pax", "/bin/tcsh,csh", "/bin/kill", "/bin/ps", "/bin/test", "/bin/dash", "/bin/ksh", "/bin/pwd", "/bin/unlink", "/bin/date", "/bin/launchctl", "/bin/rm", "/bin/wait4path", "/bin/dd", "/bin/link", "/bin/rmdir", "/bin/zsh"]

len_of_valid_comands = len(vailabe_comands)
len_of_pipes = len(pipes)

while (True):
	index_comand = random.randint(0, len_of_valid_comands - 1)
	index_pipe = random.randint(0, len_of_pipes - 1)
	comand = vailabe_comands[index_comand] + " " + pipes[index_pipe]
	print(comand)