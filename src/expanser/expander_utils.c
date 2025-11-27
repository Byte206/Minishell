#include "../../includes/minishell.h"

char  *get_env_value(t_env *env, char *name)
{
  while (env)
  {
    if (ft_strcmp(env->name, name) == 0)
        return (env->value);
    env = env->next;
  }
  return (NULL);
}

char *append_char_to_result(char *result, char c)
{
    char *temp;
    char str[2];
    
    str[0] = c;
    str[1] = '\0';
    temp = result;
    result = ft_strjoin(result, str);
    free(temp);
    return (result);
}

char *handle_valid_variable(char *result, char *var_name, t_env *env, int exit_status)
{
    char *var_value;
    char *temp;
    int should_free;
    
    var_value = get_var_value(env, var_name, &should_free, exit_status);
    if (var_value)
    {
        temp = ft_strjoin(result, var_value);
        free(result);
        result = temp;
        if (should_free)
            free(var_value);
    }
    return (result);
}
