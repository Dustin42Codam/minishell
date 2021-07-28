#include "minishell.h"
#include "environ.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

#define ARGS_MAX 131072
extern char	**environ;

char	*list_0[1] =
{
	NULL
};

char	*list_1[2] =
{
	"1=A",
	NULL
};

char	*list_2[3] =
{
	"1=A",
	"2=B",
	NULL
};

char	*list_3[4] =
{
	"1=A",
	"2=B",
	"3=C",
	NULL
};

static void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

static void	compare_lists(t_environ *env, char **list)
{
	t_environ	*tmp;
	size_t		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (environ_compare(tmp->key_value, list[i]) == 0)
		{
			printf("[%lu] [%s=%s] != [%s]\n", i, tmp->key, tmp->value, list[i]);
			exit(1);
		}
		tmp = tmp->next;
		i++;
	}
}

static void	compare_arrays(char **arr1, char **arr2)
{
	size_t	i;

	i = 0;
	if (arr1 == NULL || arr2 == NULL)
		return ;
	while (arr1[i] && arr2[i])
	{
		if (environ_compare(arr1[i], arr2[i]) == 0)
		{
			printf("[%lu] [%s] != [%s]\n", i, arr1[i], arr2[i]);
			exit(1);
		}
		i++;
	}
}

static void	test_deep_copy()
{
	t_environ	*env0 = environ_deep_copy(list_0);
	t_environ	*env1 = environ_deep_copy(list_1);
	t_environ	*env2 = environ_deep_copy(list_2);
	t_environ	*env3 = environ_deep_copy(list_3);
	t_environ	*env4 = environ_deep_copy(environ);
	t_environ	*env5 = environ_deep_copy(NULL);

	compare_lists(env0, list_0);
	compare_lists(env1, list_1);
	compare_lists(env2, list_2);
	compare_lists(env3, list_3);
	compare_lists(env4, environ);

	environ_free(env0);
	environ_free(env1);
	environ_free(env2);
	environ_free(env3);
	environ_free(env4);
}

static void	test_get(void)
{
	t_environ	*env0 = environ_deep_copy(environ);
	char	*value;

	value = environ_get(env0, "PWD");
	if (ft_strncmp(value, getenv("PWD"), ARGS_MAX))
		exit(2);
	value = environ_get(env0, "HOME");
	if (ft_strncmp(value, getenv("HOME"), ARGS_MAX))
		exit(2);
	value = environ_get(env0, "OLDPWD");
	if (ft_strncmp(value, getenv("OLDPWD"), ARGS_MAX))
		exit(2);
	value = environ_get(env0, "OLD");
	if (value)
		exit(2);
	value = environ_get(env0, "OLDPWDS");
	if (value)
		exit(2);
	value = environ_get(env0, "");
	if (value)
		exit(2);
	value = environ_get(env0, NULL);
	if (value)
		exit(2);
	value = environ_get(NULL, NULL);
	if (value)
		exit(2);
	value = environ_get(NULL, "PWD");
	if (value)
		exit(2);
	
	environ_free(env0);
}

static void	test_set(void)
{
	t_environ	*env0 = environ_deep_copy(environ);
	char		*value;

	value = environ_get(env0, "PWD");
	if (ft_strncmp(value, getenv("PWD"), ARGS_MAX))
		exit(2);
	value = environ_get(env0, "HOME");
	if (ft_strncmp(value, getenv("HOME"), ARGS_MAX))
		exit(2);
	value = environ_get(env0, "OLDPWD");
	if (ft_strncmp(value, getenv("OLDPWD"), ARGS_MAX))
		exit(2);
	value = environ_get(env0, "OLD");
	if (value)
		exit(2);
	value = environ_get(env0, "OLDPWDS");
	if (value)
		exit(2);
	value = environ_get(env0, "");
	if (value)
		exit(2);
	value = environ_get(env0, NULL);
	if (value)
		exit(2);
	value = environ_get(NULL, NULL);
	if (value)
		exit(2);
	value = environ_get(NULL, "PWD");
	if (value)
		exit(2);

	environ_free(env0);
}

static void	test_unset(void)
{
	t_environ	*env0 = environ_deep_copy(environ);
	char		*value;

	environ_unset(&env0, "PWD");
	value = environ_get(env0, "PWD");
	if (value)
		exit(2);

	environ_unset(&env0, "PWD");
	environ_unset(&env0, "PWD");
	environ_unset(&env0, "PWD");

	value = environ_get(env0, "HOMES");
	if (value)
		exit(2);
	value = environ_get(env0, "HOM");
	if (value)
		exit(2);

	value = environ_get(env0, "");
	value = environ_get(env0, NULL);
	value = environ_get(NULL, "");
	value = environ_get(NULL, "ABC");
	value = environ_get(NULL, NULL);

	environ_free(env0);
}

static void	test_get_array(void)
{
	t_environ	*env0 = environ_deep_copy(list_0);
	t_environ	*env1 = environ_deep_copy(list_1);
	t_environ	*env2 = environ_deep_copy(list_2);
	t_environ	*env3 = environ_deep_copy(list_3);
	t_environ	*env4 = environ_deep_copy(environ);
	t_environ	*env5 = environ_deep_copy(NULL);

	char		**arr0 = environ_get_array(env0);
	char		**arr1 = environ_get_array(env1);
	char		**arr2 = environ_get_array(env2);
	char		**arr3 = environ_get_array(env3);
	char		**arr4 = environ_get_array(env4);
	char		**arr5 = environ_get_array(env5);

	compare_arrays(arr0, list_0);
	compare_arrays(arr1, list_1);
	compare_arrays(arr2, list_2);
	compare_arrays(arr3, list_3);
	compare_arrays(arr4, environ);

	environ_free(env0);
	environ_free(env1);
	environ_free(env2);
	environ_free(env3);
	environ_free(env4);

	free_array(arr0);
	free_array(arr1);
	free_array(arr2);
	free_array(arr3);
	free_array(arr4);
}

int main(void)
{
	test_deep_copy();
	test_unset();
	test_get();
	test_set();
	test_get_array();
	return (0);
}
