/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:08:03 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 15:57:51 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

static int	ft_handle(char *cmdpath)
{
	struct stat	file;

	if (cmdpath)
	{
		stat(cmdpath, &file);
		if (S_ISDIR(file.st_mode))
		{
			ft_error("g_neobash: $: Is a directory", cmdpath);
			return (126);
		}
	}
	return (0);
}

static void	ft_handle_child(t_node *root, char *cmdpath, int *pfd)
{
	char	**my_envp;
	int		ex;

	ft_close_pfds(pfd);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (root->iol)
	{
		ex = ft_io(root, 0);
		if (ex)
			exit(ex);
	}
	if (!cmdpath)
	{
		ft_error("g_neobash: command not found: $", g_neobash.argss[0]);
		exit(127);
	}
	else
	{
		my_envp = get_my_envp();
		execve(cmdpath, g_neobash.argss, my_envp);
		perror("execve");
		exit(1);
	}
}

static int	ft_run_cmd(t_node *root, char *cmdpath, int *pfd)
{
	int	ex;

	ex = 0;
	handle_();
	g_neobash.last_child = fork();
	if (g_neobash.last_child == 0)
		ft_handle_child(root, cmdpath, pfd);
	else if (g_neobash.last_child > 0)
	{
		ex = ft_wait(g_neobash.last_child, ex);
		if (ex == 130)
			printf("\n");
		if (ex == 131)
			ft_error("Quit (core dumped)", NULL);
		ft_close_pfds(pfd);
		return (ex);
	}
	else if (g_neobash.last_child < 0)
	{
		perror("fork");
		return (1);
	}
	return (ex);
}

static int	ft_run(t_node *root, int *pfd)
{
	char	*cmdpath;
	int		ex;

	root->args = ft_expand(root->args);
	g_neobash.argss = get_cmdagrs(ft_astirisk(root));
	if (!g_neobash.argss || !*g_neobash.argss)
		return (0);
	if (is_builtin(g_neobash.argss[0]))
	{
		ex = ft_io(root, 0);
		if (ex)
			return (ex);
		ex = ex_builtins(root);
		return (ex);
	}
	else
	{
		cmdpath = get_cmd_path(grep_paths(get_my_envp()), g_neobash.argss[0]);
		if (ft_handle(cmdpath) == 126)
			return (126);
		ex = ft_run_cmd(root, cmdpath, pfd);
		return (ex);
	}
	return (g_neobash.status);
}

unsigned int	ex_cmd(t_node *root, int *pfd)
{
	int	ex;

	ex = 0;
	if (root->args)
	{
		ex = ft_run(root, pfd);
		return (ex);
	}
	else
	{
		ex = ft_io(root, 1);
		if (ex)
			return (ex);
	}
	return (ex);
}
