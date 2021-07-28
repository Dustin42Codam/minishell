#include "terminal_capabilities.h"
#include "libft.h"

void	clear_input_line(t_input_line **line)
{
	t_input_line	*tmp;

	if (*line == NULL)
		return ;
	while ((*line)->next)
	{
		tmp = (*line)->next;
		delete_input_line_node(line);
		*line = tmp;
	}
	delete_input_line_node(line);
}

void	copy_hist_to_input_line(char *src, t_input_line **dest)
{
	size_t	index;

	index = 0;
	if (src != NULL)
	{
		while (src[index])
		{
			insert_node_input_line(dest, new_input_line_node(src[index]));
			index++;
		}
	}
}

int	get_row_per_index(int index, int max_col)
{
	return (index / max_col);
}

void	move_cursor_to_input_node(t_prompt *prompt)
{
	t_input_line	*head;
	size_t			index;
	int				rows;

	index = 0;
	head = get_head_of_input_line(prompt->input_line);
	while (head != prompt->input_line)
	{
		index++;
		head = head->next;
	}
	rows = get_row_per_index(index, prompt->max_col);
	move_to_row_col(prompt->start_row + rows, index - rows * prompt->max_col
		+ ft_strlen(prompt->PS1));
}

t_input_line	*get_head_of_input_line(t_input_line *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->previus != NULL)
		lst = lst->previus;
	return (lst);
}
