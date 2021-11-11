#include "minishell.h"

static int  new_exit(const int *id)
{
    static int  status;

    if (id)
        status = *id;
    return(status);
}

int get_exit(void)
{
    return (new_exit(NULL));
}

void    set_exit(int id)
{
    new_exit(&id);
}