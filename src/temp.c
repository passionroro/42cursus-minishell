#include "../include/minishell.h"

void	print_list(t_node *list)
{
	printf("COMMAND LIST:\n");
	while (list)
	{
		printf("COMMAND : {%s}\n", list->content);
		list = list->next;
	}
}
