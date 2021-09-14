#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

void	expand_variables(t_token *token, t_environ *env);

char	*merge_node_strings(t_list *head);
void	append_string(char *dest, char *suffix);
void	add_substring(t_expansion *exp, char *str);
void	add_expanded_variable(t_expansion *exp);
void	do_variable_expansion(t_token *token, t_environ *env);
void	free_substrings(t_list *substrings);
void	init_expansion(t_expansion *exp);
void	get_keyvalue(t_expansion *exp, char *str, t_environ *env);
int		is_valid_variable_char(char c);
int		check_expansion(t_token *token);
void	split_words(t_token *token);
char	**word_splitter(char const *s, const char *delim);

#endif
