# Minishell
Create your own shell. In C.
## The subject
The aim of this project if pretty straight forward : we have to create a shell, a unix command line interpreter, in c. For the project to be completed, it must respect a certain conditions :
- Display a prompt while waiting for a new order
- Find and launch the right executable : `ls`
- Do not use more than one global variable.
- Manage '' and ""
- Implement redirections : <, <<, >, >>
- Implement pipes : `ls | wc`
- Manage environment variables : `echo $HOME`
- Manage $?
- Manage ctrl-C, ctrl-D and ctrl-\ which must work as in bash
- Implement builtins : echo, export, unset, env, pwd, cd and exit

Overall it was a super interesting project, pretty long and complicated to understand at first, but soooooo useful to learn how a shell works and learn to work in a team and make good use of `git`.
## Our code
First we open a prompt. It will pend until we send it an input.
```c
while (1)
    input = readline("[prompt]$ ");
```
Then the parsing. The main idea is to split the commands between every '|' character and use link the commands with linked lists. It's also a good time to check for quotes because bash doesn't handle `"cat | ls"` and `cat | ls` the same way.

Once the parsing is done, it is time to execute the commands. It will be mandatory to `fork()`, therefore the commands is executed in a child process and the _minishell_ keeps on running. Be careful, builtins command must not be forked !

Then we handle pipes. Taking `ls | wc` as an example, the the output of `ls` must become the input of `wc` (see `dup2()` command).

Have a look ! :
```c
int	pipe_it_up(t_minishell *sh, t_node *com)
{
	if (var_init(sh, com) != 0) //parsing : creating a linked list and trimmimg white spaces
		return (command_not_found(sh, com));
	remove_quotes(com); //"ls" becomes ls
	pipe(sh->pipe_fd);  //creating file descriptors to change the input and the output :)
	com->id = fork();   //creating a child process to execute the command
   	 ...
		if (com->next != NULL)
			dup2(sh->pipe_fd[1], 1);    //changing the output
  	  ...
	close(sh->pipe_fd[1]);      //
	dup2(sh->pipe_fd[0], 0);    // changing the input
	close(sh->pipe_fd[0]);      //
	return (free_var_init(sh, com, 0));
```
