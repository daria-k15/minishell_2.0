/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:09:16 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/14 12:14:26 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_node(char *env_name, char *wd, t_env **env_list)
{
	t_env	*current;
	char	*tempvalue;
	char	*directory[2];

	current = env_exists(env_list, env_name);
	if (current)
	{
		tempvalue = current->value;
		current->value = ft_strdup(wd);
		free(tempvalue);
	}
	else
	{
		directory[0] = ft_strdup(env_name);
		directory[1] = ft_strdup(wd);
		create_env_node(env_list, directory);
	}
}

void change_dir(char *path, t_env **env_list, char *cwd)
{
	if (chdir(path))
		ft_putendl_fd("Error: the path is incorrect", 2);
    else
      {
		change_node("OLDPWD", cwd, env_list);
		change_node("PWD", path, env_list);
      }
}

void	cd_to_home(char *cwd, t_env **env_list) //exit in case of err?
{
	t_env	*home;
	t_env	*current;
	char	*tempvalue;
	char	*directory[2];
    
    home = env_exists(env_list, "HOME");
    if (home)
      change_dir(home->value, env_list, cwd);
    else
      ft_putendl_fd("HOME not set", 2);
}

void cd_builtin(char **cmd_array, t_env **env_list)
{
  char *cwd;
  t_env *current;
  char *tempvalue;
  char *directory[2];

  cwd = getcwd(NULL, 0);
  if (!cmd_array[1])
    cd_to_home(cwd, env_list);
  else
    change_dir(cmd_array[1], env_list, cwd);
  free_array(cmd_array);
  free(cwd);
}