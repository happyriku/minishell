#include "minishell.h"
#include <string.h>

bool    is_metacharacter(char c)
{
    return (c && strchr("|&;()<>\n", c));
}

char    *get_operator(char **rest, char *line)
{
    char    *word;
    size_t  i;
    static char *opes[] = {"|", "&", "<<", ">>", "<", ">", "||", "&&", ";", ";;", "(", ")", "\n", NULL};
    
    while (*opes[i] != NULL)
    {
        if (strncmp(opes[i], line, strlen(opes[i])) == 0)
        {
            word = strndup(opes[i], strlen(opes[i]));
            if (!word)
                fatal_error("strndup");
            break ;
        }
        i++;
    }
    if (word == NULL)
        syntax_error("enexpected error");
    *rest += strlen(opes[i]);
    return (word);
}
