#include "minishell.h"

void env_builtin(char **cmd_array, t_env *start, int fdout)
{
  t_env *temp = start;

    while (temp != NULL)
    {
      if (temp->value)
      {
        ft_putstr_fd(temp->key, fdout);
        ft_putchar_fd('=', fdout);
        ft_putstr_fd(temp->value, fdout);
        ft_putchar_fd('\n', fdout);
      }
      temp = temp->next;
    }
    free_array(cmd_array);
    set_exit(0);
}

void echo_builtin(char **cmd_array, int fdout)
{
	int endl;
	int i;

	endl = 0;
	i = 1;
	if (cmd_array[1] && ft_strequal(cmd_array[1], "-n"))
	{
		endl = 1;
		while (cmd_array[i] && ft_strequal(cmd_array[i], "-n"))
			i++;
	}
	while (cmd_array[i])
	{
		ft_putstr_fd(cmd_array[i], fdout);
		if (cmd_array[i + 1])
			ft_putstr_fd(" ", fdout);
    i++;
	}
	if (endl != 1)
		ft_putstr_fd("\n", fdout);
	free_array(cmd_array);
  set_exit(0);
}

void pwd_builtin(char **cmd_array, int fdout)
{
  char *pwd;

  pwd = getcwd(NULL, 0);
  ft_putendl_fd(pwd, fdout);
  free(pwd);
  free_array(cmd_array);
  set_exit(0);
}

void unset_builtin(char **cmd_array, t_env **env_list, int fdout)
{
  t_env *deleted;
  int i;

  i = 1;
  while (cmd_array[i])
  {
    if (unset_arg_isok(cmd_array[i]))
      {
        deleted = env_exists(env_list, cmd_array[i]);
        if (deleted)
          delete_env(deleted, env_list);
      }
    else
    {
      ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
      ft_putstr_fd(cmd_array[i], STDERR_FILENO);
      ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
      set_exit(1); // ?val - сделать поле специальное со статусом?
    }
    i++;
  }
  free_array(cmd_array);
  set_exit(0); // ?val - сделать поле специальное со статусом?
}

void export_builtin(char **cmd_array, t_env **env_list, int fdout)
{  
  t_env *export_list;

  export_list = NULL;
  if (ft_arraylen(cmd_array) == 1)
  {
    export_list = env_cpy(*env_list);
    bubbleSort(&export_list);
    print_export_list(export_list, fdout);
    free_env(export_list);
  }
  else
  {
    int i = 1;
    while (cmd_array[i])
    {
      if (export_pair_isok(cmd_array[i]))
        change_envlist(cmd_array[i], env_list); 
      else
      {
        ft_putstr_fd("minishell: export: `", STDERR_FILENO);
        ft_putstr_fd(cmd_array[i], STDERR_FILENO);
        ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
        set_exit(1); // ?val - сделать поле специальное со статусом?
      }
      i++;
    }
  }
  free_array(cmd_array);
  set_exit(0);
}

int numeric(char *number)
{
  if (ft_atoi(number) == -1)
    return (0);
  return(1);
}

void exit_builtin(char **cmd_array, int fdout)
{
  if (ft_arraylen(cmd_array) == 1)
    exit(0);
  else if (!numeric(cmd_array[1]))
  {
    ft_putendl_fd("exit", STDERR_FILENO);
    ft_putstr_fd("minishell: exit:", STDERR_FILENO);
    ft_putstr_fd(cmd_array[1], STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
    free_array(cmd_array); //do we need it to do here?
    exit(255);
  }
  else if (ft_arraylen(cmd_array) == 2)
    exit((int)ft_atoi(cmd_array[1])); //change to long long int and use in not_numeric
  else
  {
    	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			set_exit(1);
			return ;
  }
}


