#include "../../includes/minishell.h"

static void normalize_tabs(char *s)
{
    int i = 0;
    while (s && s[i])
    {
        if (s[i] == '\t')
            s[i] = ' ';
        i++;
    }
}

static void free_parts(char **parts)
{
    int i;

    if (!parts)
        return;
    i = 0;
    while (parts[i])
    {
        free(parts[i]);
        i++;
    }
    free(parts);
}

static void insert_remaining_parts(t_token *after, char **parts)
{
    int     j;
    t_token *newtok;

    j = 1;
    while (parts[j])
    {
        if (parts[j][0] != '\0')
        {
            newtok = new_token();
            if (newtok)
            {
                newtok->value = ft_strdup(parts[j]);
                newtok->type = TOKEN_WORD;
                newtok->quote_type = QUOTE_NONE;
                newtok->joined = 0;
                newtok->next = after->next;
                after->next = newtok;
                after = newtok;
            }
        }
        j++;
    }
}

void apply_field_splitting(t_token *current, char *expanded)
{
    char    **parts;

    normalize_tabs(expanded);
    parts = ft_split(expanded, ' ');
    if (parts && parts[0] && parts[1])
    {
        t_token *insert_after = current;

        free(current->value);
        current->value = ft_strdup(parts[0]);
        current->joined = 0;
        insert_remaining_parts(insert_after, parts);
    }
    else
    {
        free(current->value);
        current->value = expanded;
        expanded = NULL;
    }
    free_parts(parts);
    if (expanded)
        free(expanded);
}
