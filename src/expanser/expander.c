
#include "../../includes/minishell.h"

char *get_var_name(char *str, int *len)
{
    int i;
    char *var_name;
    
    i = 0;
    if (str[i] == '?')
    {
        *len = 1;
        var_name = malloc(sizeof(char) * 2);
        var_name[0] = '?';
        var_name[1] = '\0';
        return (var_name);
    }
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    *len = i;
    if (i == 0)
        return (NULL);
    var_name = ft_substr(str, 0, i);
    return (var_name);
}

char *get_var_value(t_env *env, char *var_name, int *should_free, int exit_status)
{
    char *value;
    
    *should_free = 0;
    if (ft_strcmp(var_name, "?") == 0)
    {
        *should_free = 1;
        return (ft_itoa(exit_status));  // ✅ Usa el parámetro
    }
    value = get_env_value(env, var_name);
    return (value);
}


static char *process_variable(char *result, char *str, int *i, t_env *env, int exit_status)
{
    char *var_name;
    int var_len;
    char *temp;
    char str_dollar[2];
    
    (*i)++;
    var_name = get_var_name(&str[*i], &var_len);
    if (var_name)
    {
        result = handle_valid_variable(result, var_name, env, exit_status);
        free(var_name);
        *i += var_len;
    }
    else
    {
        str_dollar[0] = '$';
        str_dollar[1] = '\0';
        temp = result;
        result = ft_strjoin(result, str_dollar);
        free(temp);
    }
    return (result);
}

static char *expand_string(char *str, t_env *env, t_quote_type quote_t, int exit_status)
{
    char *result;
    int i;
    
    result = ft_strdup("");
    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && quote_t != QUOTE_SINGLE)
            result = process_variable(result, str, &i, env, exit_status);  // ✅ Pasa exit_status
        else 
        {
            result = append_char_to_result(result, str[i]);
            i++;
        }
    }
    return (result);
}

void expander(t_token *tokens, t_env *env, int exit_status)
{
    t_token *current;
    char *expanded;
    
    current = tokens;
    while (current)
    {
        if (current->type == TOKEN_WORD)
        {
            expanded = expand_string(current->value, env, current->quote_type, exit_status);
            free(current->value);
            current->value = expanded;
        }
        current = current->next;
    }
}
