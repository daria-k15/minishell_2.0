#ifndef MINISHELL
# define MINISHELL

#include "./libft/include/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef struct s_env
{
  char          *key;
  char          *value;
  struct s_env  *next;
} t_env;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	char			*value;
	int				prior;
}					t_ast;

typedef struct s_ctrl
{
	t_env	*env;
	int		pid;
	int		fd_out;
	int		fd_in;
}			t_ctrl;

typedef struct s_ast_data
{
	int *pipe;
	int *file;
	int out;
	int in;
}		t_ast_data;




//-------ast.c
t_ast*	create_node(char *value);
void	insert_left(t_ast **ast, char *value);
void	add_value(t_ast **ast, char *value);
void	tree_print_rec(t_ast *ast, int level);
t_ast*	tree_create(t_ast *ast, char **array);
void	ast_data_free(t_ast_data *val);
void	t_ctrl_free(t_ctrl *control);

/*-----parsingAstArray.c-----*/
int		check_char(char *line, char ch, int i);
char	*skip_space(char *line, int *i);
char	*single_quote_parse(char *line, int *i);
char	*slash_parse(char *line, int *i);
char	*double_quote_parse(char *line, int *i);

/*-----parsingAstArray2.c-----*/
char	*redirect2(char *tmp, char *line, int *j);
char	*redirect_parse(char *line, int *i, char **envp);
int		find_redir(char *line);
char	**add_val(char **array, char *val);
char	*parsing2(char *line);

/*-----parsingAstArray3.c-----*/
char	*new_line(char *line, int *i);
char	**pars_to_array(char *line, char **array, char **envp, int *i);
char	**parsing(char *line, char **envp);


//------dollar_parse.c------//
char	*parse_dollar(char *line, int *i, char **envp);
int		if_key(char c);


t_ast*	insert_val(t_ast **ast, char *value);
 int check_arg(char *arg);
 void tree_print_rec(t_ast *ast, int level);
 t_ast*	create_node(char *value);
void	add_value(t_ast **ast, char *value); 
int check_redir(t_ast *ast);
void tree_free(t_ast **tree);


/* -- builtins -- */

void env_builtin(char **cmd_array, t_env *start, int fdout);
void echo_builtin(char **cmd_array, int fdout);
void pwd_builtin(char **cmd_array, int fdout);
void cd_builtin(char **cmd_array, t_env **env_list, int fdout);
void exit_builtin(char **cmd_array, int fdout);
void export_builtin(char **cmd_array, t_env **env_list, int fdout);
void unset_builtin(char **cmd_array, t_env **env_list, int fdout);

/* -- env funcs -- */

char	**ft_split_env(char const *s, char c);
void print_export_list(t_env *start, int fdout);
void ft_swap(t_env **start, t_env *a, t_env *b);
void bubbleSort(t_env **start);
t_env	*ft_lastnode(t_env *lst);
int create_env_node(t_env **lst, char **d);
t_env *env_init(char **env);
t_env *env_cpy(t_env *head);
void free_env(t_env *head);
int export_pair_isok(char *pair);
t_env *env_exists(t_env **env_list, char *key);
void change_envlist(char *new_env, t_env **env_list);
void delete_env(t_env *deleted, t_env **env_list);
int unset_arg_isok(char *arg);

/* -- may be added to the lib -- */

int	ft_strequal(const char *str1, const char *str2);
size_t	ft_arraylen(char **str);
int		 rl_on_new_line(void);
void		rl_replace_line(const char *text, int clear_undo);


/* ---- executor ------ */

//-----utils.c-----//
int	check_arg(char *arg);
int check_hero(t_ast *ast);
int	check_redir(t_ast *ast);
void	ft_err(char *str);
void	free_array(char **str);

//-----utils_2.c-----//
int	ft_strequal(const char *str1, const char *str2);
int	check_redir_pipe(char *line);

//-----signals.c-----//
void	handlerint(int signal);
//void	sighandler(void);
char	*start_loop(void);
void	tree_sighandler(void);

//------envp.c-----//
char	*path_handler(char *cmd, char **env);
char **env_array(t_env **env_list);
void  binary_command(t_ast *ast, char **cmd_array, t_env **env_list, t_ctrl *control, t_ast_data *val);

//-----tree_handling.c-----//
void tree_handle(t_ast *ast, t_ctrl *control, char **envp);
void    go_through_nodes(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp);
void    right_redir(t_ast *ast, t_ctrl *control, t_ast_data *val,char **envp);
void	left_redir(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp);
void pipe_func(t_ast *ast, t_ctrl *control, t_ast_data *val,char **envp);
void ctrl_free(t_ctrl *control);
//----set_exit.c-----//
static int  new_exit(const int *id);
int get_exit(void);
void    set_exit(int id);


#endif