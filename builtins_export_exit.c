/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:28:52 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/14 12:29:28 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

static int numeric(char *number)
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