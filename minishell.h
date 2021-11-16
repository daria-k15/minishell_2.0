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
	char	*mininame;
	t_env	*env_list;
	int		pid;
	int		fd_out;
	int		fd_in;
	int		print;
}			t_ctrl;

typedef struct s_ast_data
{
	int *pipe;
	int *file;
	int out;
	int in;
}		t_ast_data;




/*-------ast.c-----*/
t_ast	*tree_create(t_ast *ast, char **array);
t_ast	*node_create(char *value);
t_ast	*firstnode(t_ast **ast, t_ast *new, t_ast *tmp, char *value);
t_ast	*add_value(t_ast **ast, char *value);

/*-----ast_2.c-----*/
int		return_prior(char *value);
t_ast	*addtoend(t_ast **ast, t_ast *new, t_ast *tmp);
t_ast	*addnode(t_ast **ast, t_ast *new, t_ast *tmp, char *value);
t_ast	*fnode(t_ast **ast, t_ast *new, t_ast *tmp, char *value);

/*---binary_command.c---*/
char	*path_handler(char *cmd, char **env);
static void	execute_cmd(t_ast *ast, char **array, t_ctrl *ctrl, t_ast_data *val);
void	binary_command(t_ast *ast, char **array, t_ctrl *ctrl, t_ast_data *val);

/*---builtins_cd.c-----*/
void	change_node(char *env_name, char *wd, t_env **env_list);
void	change_dir(char *path, t_env **env_list, char *cwd);
void	cd_to_home(char *cwd, t_env **env_list);
void	cd_builtin(char **cmd_array, t_env **env_list);

/*----builtins_exit.c-----*/
static int	numeric_condition(unsigned long long *exit_num, int neg);
static int	numeric(char *number, unsigned long long *exit_num);
void	exit_builtin(char **cmd_array, t_ctrl *control, int fdout);

/*-----builtins_export-----*/
void	bubble_sort(t_env **start);
static void	export_add_env(char **cmd_array, t_env **env_list);
void	export_builtin(char **cmd_array, t_env **env_list, int fdout);

/*-----builtins----*/
void	env_builtin(char **cmd_array, t_env *start, int fdout);
void	echo_builtin_2(char **cmd_array, int fdout, int *i, int endl);
void	echo_builtin(char **cmd_array, int fdout);
void	pwd_builtin(char **cmd_array, int fdout);
void	unset_builtin(char **cmd_array, t_env **env_list, int fdout);


//------dollar_parse.c------//
char	*parse_dollar(char *line, int *i, char **envp);
int		if_key(char c);
char	*found_k(char **envp, char *tmp);

/*-----env_functions.c-----*/
char	**ft_split_env(char const *s, char c);
void	print_export_list(t_env *start, int fdout);
void	ft_swap(t_env **start, t_env *a, t_env *b);
t_env	*ft_lastnode(t_env *lst);
int	env_node_create(t_env **lst, char **d);

/*-----env_functions_2.c-----*/
t_env	*envlist_init(char **env);
t_env	*env_cpy(t_env *head);
void	free_env(t_env *head);
int	unset_arg_isok(char *arg);
int	export_pair_isok(char *pair);

/*-----env_functions_3.c-----*/
t_env	*env_exists(t_env **env_list, char *key);
void	change_envlist_2(t_env **env_list, char **temp, int tobejoined);
void	change_envlist(char *new_env, t_env **env_list);
void	delete_env(t_env *deleted, t_env **env_list);
char	**env_to_array(t_env **env_list);


//----exit_status.c-----//
static int  new_exit(const int *id);
int get_exit(void);
void    set_exit(int id);

/*------love_norm.c------*/
char	**love_norme(char **array, int i);


/*-----parsingAstArray.c-----*/
t_ast	*node_create(char *value);
char	*skip_space(char *line, int *i);
char	*single_quote_parse(char *line, int *i);
char	*slash_parse(char *line, int *i);
char	*double_quote_parse(char *line, int *i);

/*-----parsingAstArray2.c-----*/
char	*redirect2(char *tmp, char *line, int *j);
char	*redirect_parse(char *line, int *i);
int		find_redir(char *line);
char	**add_val(char **array, char *val);
char	*parsing2(char *line, char **envp);

/*-----parsingAstArray3.c-----*/
char	*new_line(char *line, int *i);
char	**pars_to_array(char *line, char **array, char **envp, int *i);
char	**parsing(char *line, char **envp);



/*-------printAst.c-----------*/
void	printtabs(int n);
void	tree_print_rec(t_ast *ast, int level);


//------redirects_heredoc.c----//
void	heredoc_func(t_ast *ast, t_ctrl *control);
void create_files(t_ast_data *val, int fd);


//--------redirects.c-------/
void	left_redir(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp);
void	right_redir(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp);
void	add_new_pipes(t_ast_data *td, int fd);
void	pip_func2(t_ctrl *control, int fork_pid[], int pipe_des[], int *status);
void	pipe_func(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp);


/*-----signals.c-----*/
void	handlerint(int signal);
void	sighandler(void);
void	sigproc(void);

/*------signals_2.c-----*/
void	tree_sighand(int signal);
void	tree_sighandler(void);
void	handlerquit(int signum);


//------split_values.c-----//
t_ast_data	*ast_data_init(void);
char	*tree_single_quote(char *line, int *i);
char	*tree_skip_space(char *line, int *i);
char	**split_values(char *line, char **env);
char	**split_values2(char *line, char **env, char **array);

/*-----split_values2.c-----*/
char	*tree_double_quote2(char *line, int *i, char **envp, int j);
char	*tree_double_quote(char *line, int *i, char **envp);


//------tree_handling.c------//
void clean_node(t_ast *ast, t_ctrl *data, t_ast_data *val);
void empty_cmd(t_ast *ast, t_ctrl *data, t_ast_data *val, char **array);
void cmd_commands(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp);
void ctrl_free(t_ctrl *control);
void ast_data_default(t_ast_data *val);


//-----utils.c-----//
int	check_arg(char *arg);
int check_heredoc(t_ast *ast);
int	check_redir(t_ast *ast);
void	ft_err(char *str);


//-----utils_2.c-----//
int	ft_strequal(const char *str1, const char *str2);
int	check_redir_pipe(char *line);
void	free_array(char **str);
size_t	ft_arraylen(char **str);


//---------tree.c----------//
void	ast_data_free(t_ast_data *val);
void	go_through_nodes(t_ast *ast, t_ctrl *c, t_ast_data *val, char **envp);
void	tree_handle(t_ast *ast, t_ctrl *control, char **envp);
void	tree_free(t_ast **tree);
void	tree(char **array, t_ctrl *control, char **envp);

#endif