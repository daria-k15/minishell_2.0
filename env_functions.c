#include "minishell.h"

char	**ft_split_env(char const *s, char c)
{
    char	**str_array;
    int i;

    i = 0;
    str_array = (char **)malloc(sizeof(char *) * 3);
    if (str_array == NULL)
        return (NULL);
    while (s[i] && s[i] != c)
        i++;
    str_array[0] = ft_substr(s, 0, i);
    if (i + 1 < (int)ft_strlen(s))
    {
        i++;
        str_array[1] = ft_substr(s, i, ft_strlen(s) - i);
    }
    else
        str_array[1] = ft_strdup("");
        str_array[2] = NULL;
        return (str_array);
}

void print_export_list(t_env *start, int fdout)
{
    t_env *temp = start;

    while (temp != NULL)
    {
        if (!ft_strequal(temp->key, "_"))
        {
          ft_putstr_fd("declare -x ", fdout);
          ft_putstr_fd(temp->key, fdout);
          if (temp->value)
          {
            ft_putchar_fd('=', fdout);
            ft_putchar_fd('"', fdout);
            ft_putstr_fd(temp->value, fdout);
            ft_putchar_fd('"', fdout);
          }
          ft_putchar_fd('\n', fdout);
        }
        temp = temp->next;
    }

}

/* function to swap data of two nodes a and b*/
void ft_swap(t_env **start, t_env *a, t_env *b)
{
    t_env *temp;
    t_env *temp2;

    temp = NULL;
    temp2 = NULL;
    if (!a || !b || !start)
		  return ;
    if (ft_strncmp((*start)->key, a->key, ft_strlen(a->key)) != 0)
    {
      temp = (*start);
      while (ft_strncmp(temp->next->key, a->key, ft_strlen(a->key)))
          temp = temp->next;
      temp->next = b;
      temp2 = b->next;
      b->next = a;
      a->next = temp2;
    }
    else
    {
      (*start) = b;
      a->next = b->next;
      (*start)->next = a;
    }
}


t_env	*ft_lastnode(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int env_node_create(t_env **lst, char **d)
{
  t_env *new;

  if (!d || !lst)
		return 1;
  new = (t_env *)malloc(sizeof(t_env));

  if (!d || !new)
    return 1; //perror
  new->key = d[0];
  new->value = d[1];
  new->next = NULL;
	if (!*lst)
		*lst = new;
	else
		ft_lastnode(*lst)->next = new;
  return 0;
}
  
t_env *envlist_init(char **env)
{
    t_env *start;
    int n;
    size_t a;

	  n = 0;
    a = 0;
    start = NULL;
	  while (a < ft_arraylen(env) && !n)
    {
      char **d = ft_split_env(env[a++], '=');
      n = env_node_create(&start, d);
    }
		return start;
}
  
// Function to create a copy of a linked list
t_env *env_cpy(t_env *head)
{
    t_env *newnode;

    newnode = NULL;
    if (head == NULL) 
        return NULL;
    else {
        // Allocate the memory for new Node
        // in the heap and set its data
      newnode = (t_env *)malloc(sizeof(t_env));
      newnode->key = head->key;
      newnode->value = head->value;
  
        // Recursively set the next pointer of
        // the new Node by recurring for the
        // remaining nodes
      newnode->next = env_cpy(head->next);
      return newnode;
    }
}

void free_env(t_env *head)
{
  t_env *tmp;

    if (head)
    {
      tmp = head;
      free_env(head->next);
      free(tmp);
      tmp = NULL;
    }
}

int unset_arg_isok(char *arg)
{
  int i;

  i = 0;
  while (arg[i])
    if ((arg[i] != '_' && !ft_isalnum(arg[i++])) || ft_isdigit(arg[0]))
      return (0);
  return (1);
}

int export_pair_isok(char *pair)
{
  int i;

  i = 0;
  while (pair[i])
  {
    if (i == 0 && (ft_isdigit(pair[i]) || pair[i] == '=' || pair[i] == '+'))
      return (0);
    if ((pair[i] == '+' && pair[i + 1] && pair[i + 1] == '=') || pair[i] == '=')
      return (1);
    if (pair[i] != '_' && !ft_isalnum(pair[i]))
      return (0);
    i++;
  }
  return (1);
}

t_env *env_exists(t_env **env_list, char *key)
{
  t_env *temp;
  temp = *env_list;
  while (temp) 
  {
    if (ft_strequal(temp->key, key))
      return(temp);
    temp = temp->next;
  }
  return (NULL);
}

void change_envlist(char *new_env, t_env **env_list)
{
    char **temp;
    int tobejoined;
    char *temp2;
    t_env *current;
    char *tempvalue;
    
    tobejoined = 0;
    temp = ft_split_env(new_env, '=');
    if (temp[0][ft_strlen(temp[0]) - 1] == '+')
    {
      temp2 = temp[0];
      temp[0] = ft_substr(temp[0], 0, ft_strlen(temp[0]) - 1);
      free(temp2);
      tobejoined++;
    }
    current = env_exists(env_list, temp[0]);
    if (current)
    {
      tempvalue = current->value;
      if (tobejoined)
        current->value = ft_strjoin(current->value, temp[1]);
      else
        current->value = temp[1];
      free(tempvalue);
    }
    else
      env_node_create(env_list, temp);
}

void delete_env(t_env *deleted, t_env **env_list)
{
    t_env *ptr1;
  
    ptr1 = (*env_list);
    while (!ft_strequal(ptr1->next->key, deleted->key)) 
      ptr1 = ptr1->next;
    ptr1->next = deleted->next;
    free(deleted->key);
    free(deleted->value);
    free(deleted);
}

char **env_to_array(t_env **env_list)
{
  int i;
  t_env *tmp;
  char **array;
  char *equal;

  i = 0; 
  tmp = *env_list; 
  while (tmp)
  {
    i++;
    tmp = tmp->next;
  }
  array = (char **)malloc(sizeof(char *) * i);
  if (!array)
    return (NULL);
  tmp = *env_list;
  i = 0;
  while (tmp)
  {
	equal = ft_strjoin(tmp->key, "="); //protect
    array[i] = ft_strjoin(equal, tmp->value); //protect and clean what was created
    i++;
    tmp = tmp->next;
    free(equal);
  }
  array[i] = NULL;
  return array;
}