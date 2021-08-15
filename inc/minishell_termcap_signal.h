#ifndef TERMINAL_CAPABILITIES_H
# define TERMINAL_CAPABILITIES_H
# include <signal.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_input_line
{
	struct s_input_line	*next;
	struct s_input_line	*previus;
	char				c;
}		t_input_line;

typedef struct s_history
{
	struct s_history	*next;
	struct s_history	*previus;
	char				*str;
}		t_history;

typedef enum s_key_sizes
{
	SIGNAL_OR_REGULAR_KEY_PRESS = 1,
	ARROW_KEY = 3,
	INVALID_KEY = -1
}		t_key_sizes;

typedef struct s_promt_color
{
	char	*GREEN;
	char	*RED;
	char	*BLUE;
	char	*ESC_COLOR;
}		t_prompt_color;

typedef struct s_prompt_keys
{
	char	*UP;
	char	*DOWN;
	char	*RIGHT;
	char	*LEFT;
	char	*DEL;
	char	*RETURN;
}		t_prompt_keys;

typedef struct s_signals
{
	char			signal_char;
	int			signal_NO;
	void			(*hook_function)(int);
	struct s_signals	*next;
}		t_signals;

typedef struct s_prompt
{
	char			*PS1;
	int				max_col;
	int				max_row;
	int				start_row;
	int				start_col;
	t_history		*history;
	t_input_line	*input_line;
	char			*tmp_history;
	t_signals		*signals;
}		t_prompt;

/****************************************************************
****************SIGNAL_PART_OF_PROMPT****************************
****************************************************************/

int			call_function_by_sig(char *user_input, t_prompt *prompt);
t_signals	*init_signals(void);
bool			is_regular_key_or_sig(int message_len);
bool			is_signal(char user_input, t_signals *signal);

/****************************************************************
****************TERMCAP_FUNC*************************************
****************************************************************/

void			ring_bell(void);
void			move_right_one_space(void);
void			move_left_one_space(void);
void			delet_char_at_cursor_pos(void);
void			open_insert_mode(void);
void			escape_insert_mode(void);
void			move_one_row_up(int row, int col);
void			move_to_end_of_line(int row, int col);
void			move_one_row_down(int row, int col);
void			move_to_start_of_line(int row, int col);
void			move_to_start_row(int row, int col);
void			move_to_row_col(int row, int col);
void			del_char(t_prompt *prompt);
void			del_curent_line(void);

/****************************************************************
****************COLOR_FUNC***************************************
****************************************************************/

char			*apply_color(char *message, char *color);

/****************************************************************
****************DDL/INPUT_LINE_MAIPULATIOIN**********************
****************************************************************/

void			pop_a_node_input_line_end(t_input_line **curent);
void			pop_a_node_input_line_midle(t_input_line **curent);
void			pop_a_node_input_line_start(t_input_line **curent);
void			pop_a_node_input_line(t_input_line **lst);
int				get_size_of_input_line_dll(t_input_line *lst);
void			delete_input_line_node(t_input_line **node);
void			clear_input_line(t_input_line **line);
char			*copy_input_line(t_input_line *input_line);
void			insert_node_input_line(t_input_line **lst, t_input_line *node);
void			insert_node(t_input_line **head);
void			move_cursor_to_input_node(t_prompt *prompt);
t_input_line	*new_input_line_node(char c);

/****************************************************************
****************DDL/HISTORY_LINE_MAIPULATIOIN********************
****************************************************************/

void			copy_hist_to_input_line(char *src, t_input_line **dest);
void			update_history_node(t_history **dest, char *src);
void			update_tmp_history(t_prompt **prompt);
void			copy_hist_to_tmp_hist(char *src, char **dest);
void			insert_node_history_start(t_history **lst, t_history *node);
void			move_history_to_start(t_prompt **prompt);
void			history_revers(t_prompt *prompt);
void			history_travers(t_prompt *prompt);
t_history		*new_history_node(char *str);
void			delete_history_node(t_history **node);
void			clear_history(t_prompt *prompt);

/****************************************************************
****************I/O FUNCTIONS************************************
****************************************************************/

int			ft_readline(char **line, t_prompt *prompt);
int				read_user_input(char *user_input);
void			print_input_line(char *line);
void			print_prompt(t_prompt *prompt);
void			write_input_line(t_input_line *input_line);
int				ft_putchar_int(int c);
int				write_to_stdout(char *str);

/****************************************************************
****************CAN/IS_FUNCTIONS*********************************
****************************************************************/

bool			can_move_cursor_left(t_prompt *prompt, int row, int col);
bool			can_move_right(t_prompt *prompt, int row, int col);
bool			is_previus_previus_input_line_node_NULL(t_input_line *node);
bool			is_next_input_line_node(t_input_line *input_line);
bool			is_cursor_at_lats_column(t_prompt prompt, int col);
bool			is_cursor_on_prompt(t_prompt *prompt, int row, int col);
bool			is_cursor_at_start_of_line(int col);
bool			is_input_line_node_null(t_prompt *prompt);
bool			is_input_node_first(t_input_line *curent);
bool			is_input_node_last(t_input_line *curent);
bool			is_cursor_at_end_of_line(t_prompt *prompt, int col);
bool			is_cursor_at_last_column(t_prompt *prompt, int row, int col);
bool			is_history_null(t_prompt *prompt);
bool			is_input_key_down_arrow(char *c);
bool			is_input_key_left_arrow(char *c);
bool			is_input_key_right_arrow(char *c);
bool			is_input_key_up_arrow(char *c);
bool			is_input_return(char *user_input);
bool			is_next_prev_node_null(t_prompt *prompt);
bool			is_str_key(char *key, char *c, int size_of_key);
bool			is_previus_history_node_null(t_prompt *prompt);
bool			is_next_history_node_null(t_prompt *prompt);
bool			is_previus_input_line_node_null(t_input_line *input_line);
bool			is_next_input_line_node_null(t_prompt *prompt);
bool			is_string_NULL(char *str);
bool			is_del_char(char *user_input);
bool			is_regular_char(char user_input);

/****************************************************************
****************GET_FUNCTIONS************************************
****************************************************************/

int				get_row_per_input_line(t_prompt *prompt);
int				get_row_per_index(int index, int max_col);
char			*get_string_entry(char *key_id);
int				get_curent_col(char *buf, int row);
char			*get_curent_cursor_pos(void);
int				get_curent_row(char *buf);
int				get_end_of_line(t_prompt *prompt);
int				get_max_amount_of_col(void);
int				get_max_amount_of_col(void);
int				get_max_amount_of_row(void);
int				get_max_amount_of_row(void);
char			*get_prompt_message(void);
int				get_prompt_message_size(t_prompt *prompt);
int				get_ttyfd(void);
t_input_line	*get_head_of_input_line(t_input_line *lst);
t_history		*get_history_head(t_history *lst);
int				get_size_of_input_line_dll(t_input_line *lst);

/****************************************************************
****************SET_FUNCTIONS************************************
****************************************************************/

void			set_first_node(t_prompt **prompt, char *updated_line);

/****************************************************************
****************UTIL_FUNCTIONS***********************************
****************************************************************/

void			match_key_with_fuc(char *user_input, t_prompt *prompt);
void			insert_char(char *user_input, t_prompt *prompt);
int				ft_putchar_ret_int(int c);
void			minishell_putstr(char *str);
int				failed_to_write_exit_code(char *buf);
void			update_prompt(t_prompt **prompt, int sig);
void			update_node(t_prompt **prompt, char *updated_line);
void			update_line(t_prompt **prompt);
void			ask_cursor_position(int ttyfd);
int			execute_user_input(char *input, t_prompt *prompt, int msg_len);
void			recive_cursor_position(char *buf, int fd);
bool			react_to_left_arrow_key_press(t_prompt *prompt);
void			react_to_right_arrow_key_press(t_prompt *prompt);
void			ft_free_prompt(t_prompt *prompt);
void			clear_user_input(char *buf, int size);
void			clear_input_2(t_prompt *prompt);
void			clear_input(t_prompt *prompt);

/****************************************************************
**		INIT_FUNCTIONS***********************************
****************************************************************/

t_prompt_color	init_prompt_color(void);
t_prompt_keys	init_prompt_keys(void);
void			init_prompt(t_prompt **prompt);

#endif
