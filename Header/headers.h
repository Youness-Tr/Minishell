/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:41:39 by kali              #+#    #+#             */
/*   Updated: 2024/08/14 23:09:41 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include "../Libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define RED "\033[30;31m"
# define G "\033[1;32m"
# define ORG "\033[0;33m"
# define PER "\033[97m"
# define CY "\033[96m"
# define RES "\033[0m"

# define PROMPT "neoshell->$ "

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			visible;
	struct s_env	*next;
}					t_env;

typedef enum s_token_t
{
	WRD,
	INPUT,
	APPEND,
	HEREDOC,
	REDIRECT,
	L_PARENT,
	R_PARENT,
	AND,
	OR,
	PIPE,
	SYNTAX
}					t_token_t;

typedef struct s_token
{
	char			*value;
	t_token_t		type;
	struct s_token	*next;
}					t_token;

typedef enum s_io_t
{
	OUT,
	IN,
	HERE_DOC,
	APP,
}					t_io_t;

typedef struct s_io
{
	t_io_t			type;
	int				here_doc;
	char			*value;
	char			*exp_val;
	struct s_io		*next;
}					t_io;

typedef enum s_node_t
{
	AND_N,
	OR_N,
	PIPE_N,
	CMD_N,
	IO_N,
	NOTHING
}					t_root_t;

typedef struct s_node
{
	t_root_t		type;
	t_io			*iol;
	char			*args;
	char			*exp_val;
	bool			is_block;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_leak
{
	void			*address;
	struct s_leak	*next;
}					t_leak;

typedef struct s_shell
{
	char			*line;
	int				np;
	t_token			*tokens;
	t_token			*cur_tok;
	t_node			*tree;
	int				status;
	int				prs_state;
	pid_t			last_child;
	char			**envp;
	char			**sub;
	char			**paths;
	int				hdoc;
	char			*tmp;
	char			*palestine;
	t_env			*envl;
	t_env			*envl_dup;
	bool			app;
	int				flag;
	t_leak			*leaks;
	int				fd[2];
	int				in;
	int				out;
	int				count;
	int				level;
	char			**argss;
	bool			exp_here;
	bool			here_dc_ex;
}					t_shell;

extern t_shell		g_neobash;

void				get_env_list(char **env);
t_leak				*ft_leaks_lstlast(t_leak *lst);
void				ft_leaks_lstadd_back(t_leak **lst, t_leak *newx);
t_leak				*ft_leaks_lstnew(void *var);
void				*ft_malloc(size_t size);
t_leak				*ft_lstlastv2(t_leak *lst);
char				*join_args(char **s);
void				ft_lexer(void);
void				give_token(void);
bool				ft_coutquotes(void);
void				ft_err(char *err, int flag);
bool				check_spcial(char c);
bool				ft_check_io_pairs(char *line, int i);
void				ft_lstadd_backv3(t_token **lst, t_token *newx);
t_token				*ft_lstnewv3(char *var, t_token_t token);
t_token				*ft_lstlastv3(t_token *lst);
t_token_t			set_token(int i);
bool				is_badchar(char *c);
bool				is_whitespaces(char line);
int					count_whitespaces(char *line, int i);
int					count_inside_quotes(int i, char q);
bool				is_quotition(char i);
void				ft_lexical(int ntoken);
void				*ft_malloc(size_t size);
void				ft_free_all(void);
t_node				*ft_parser(void);
bool				ft_argv(char **cmd);
t_node				*ft_scmd(void);
t_node				*ft_left_hand(void);
t_node				*ft_rdp(int p);
int					ft_precedence(t_token_t tp);
bool				is_pair(void);
bool				is_io(void);
void				ft_skip_tok(void);
void				set_state(int state);
t_node				*ft_newnode(t_root_t node_t);
char				*ft_strjoinc(const char *s1, const char *s2, char c);
bool				create_iol(t_io **io, t_io_t io_t);
t_io				*create_io_node(char *val, t_io_t type);
t_io_t				get_type(t_token_t tk);
void				ft_addback_io_node(t_io **iop, t_io *new);
int					bt_cd(char **s);
int					skip(char *s);
void				ft_strcpy(char *dst, char *src, char c);
size_t				ft_strlenc(char *str, char c);
void				ft_echo(char *s, bool sq, bool dq);
void				ft_env(t_env *env);
void				ft_exit(char **str);
int					ft_export(char *s);
int					parse_key(char *str);
bool				search_env(char *s);
char				*handle_quote(char *line, int start);
int					ft_pwd(char **s);
void				ft_unset(char **s);
void				update_env(char *key, char *value);
void				exp_back(t_env *new);
t_env				*exp_new(char *key, char *value);
void				update_env(char *key, char *value);
char				*get_env_val(char *key);
int					count_args(char **s);
int					ft_pipes(t_node *root);
int					ft_wait(pid_t pid, int ex);
int					run_io(t_node *root);
int					ft_exec_and(t_node *root);
int					ft_exec_or(t_node *root);
void				ft_check_r(char *file);
void				ft_check_w(char *file);
void				execution(void);
int					ft_executer(t_node *root, int *pfd);
char				**get_cmdagrs(char *line);
char				**get_my_envp(void);
char				*get_cmd_path(char **paths, char *cmd);
void				heredoc_f(t_io *io, int fd[2]);
int					ft_io(t_node *root, int flag);
int					ft_app(t_io *io, int flag);
int					ft_in(t_io *io, int flag);
int					ft_out(t_io *io, int flag);
void				ft_init_io(t_node *root);
int					ex_builtins(t_node *root);
bool				is_builtin(char *str);
int					ex_pipes(t_node *root);
void				ex_rpipe(int fd[2], t_node *root);
void				ex_lpipe(int fd[2], t_node *root);
void				ft_error(char *str, char *s1);
unsigned int		ex_cmd(t_node *root, int *pfd);
void				ft_close_pfds(int *pfd);
void				ft_before_exec(t_node *root);
void				handler(int sig);
char				*normal_str(char *str, int *i);
char				*handle_squotes(char *str, int *i);
char				*handle_dquotes(char *str, int *i);
char				*dquote_str(char *str, int *i);
char				*handle_dollar(char *str, int *i);
bool				valid_char(char c);
char				*ft_expand(char *str);
void				sort_env(t_env *env);
t_env				*env_list_dup(t_env *env);
void				print_ex(t_env *env);
void				ft_export_err_msg(char *identifier);
int					skip(char *s);
char				*expand_heredoc(char *str);
char				*asterisk(char *s);
int					ft_lstsizev2(t_env *lst);
char				**get_astiriskargs(char *line);
void				ft_init_signals(void);
char				**grep_paths(char **env);
bool				synyax_before(void);
void				ft_syntax_after(void);
void				ft_rstds(void);
int					exit_parse(char **str, int *i, int *c);
int					ft_check_x(char *file);
char				*ft_astirisk(t_node *root);
char				*ft_mron(char *line, char *str, int *i);
void				handle_(void);

#endif