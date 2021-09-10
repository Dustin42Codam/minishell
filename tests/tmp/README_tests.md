Okay imagine this, unit test is the same as a tower deffence game, bet better your programm the less mosters get throw
it is more work becuase we have to map out our own work.

<h2>Signals:</h2>
	1. CTRL + C sends SIGINT to child process
	2. CTRL + D passes a EOF throw the pipe and then child should stop reading from the pipe
	3. CTRL + \ is SIGQUIT which is a hard exit
<b>How do we test this tho?</b>
These will be my opinion about how to write.
First is first <i>man signals</i>
<b><i>naturaly</i> we have ttest for meme leaks when the programm exits with a signal </b>
<h1>GET COMODRTABLE MADAFAKAS</h1>
it would make sense to make a syntaxe tree for testing 
so we have a python script for generaiting all kids of combinations of commands
we should be able to add Idea of a signal or manualy hit signals when the comands ar running
we need to leak test minibash vs leak test bash

	bash					|			Minishell
lets write this
<b>What varibles, globals, macros are affected by these signals?</b>
