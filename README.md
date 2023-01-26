# minishell

This group project is about creating a simple shell.  
Just like bash, but a little bit smaller.  
The goal was to learn how the system handles processes, file descriptors and signals.  

I also learned how to lexically analyze plain input text into seperate word-tokens and recursively parse those tokens into an abstract syntax tree.
Abstract syntax trees are data structures widely used in compilers to represent the structure of program code.
I used it to represent the structure of any given shell input command.

minishell has the following builtins to offer:  
`echo`: display a line of text (e.g. `echo hello world`)  
`env`: prints the environment  
`exit`  : causes process termination  
`export`: set the export attribute for variables (e.g. `export key=value`)  
`pwd`   : print working directory  
`unset` : unset values and attributes of variables  

The shell can also...  
- browse through command history with up and down keys  
- search and launch the right executable based on the `PATH` variable  
- handle single quotes  
- handle double quotes  
- redirect input `command < input`  
- redirect output `command > output`  
- handle heredocs `command << delimeter`
- redirect and append output `command >> output`  
- pipe output `command_1 | command_2`  
- expand environment variables `echo $HOME`  
- expand last exit status `echo $?`  
- handle ctrl-C, ctrl-D and ctrl-\ like in bash  

## Installation

```bash
$ make
```

## Running the app

```bash
$ ./minishell
