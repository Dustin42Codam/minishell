#ifndef ENVIRON_H
# define ENVIRON_H

# include "minishell.h"

t_environ	*environ_deep_copy(char **env);
char		*environ_get(t_environ *head, char *key);
void		environ_set(t_environ *head, char *key, char *value);
void		environ_add_back(t_environ **env, t_environ *new);
t_environ	*environ_new(const char *key_value);
void		environ_unset(t_environ **head, char *key);
void		environ_free(t_environ *head);
char		**environ_get_array(t_environ *env);
int			environ_compare(char *s1, char *s2);
void		environ_modify(t_environ *head, char *key, char *value);
char		*environ_get_keyvalue(char *key, char *value);

#endif
