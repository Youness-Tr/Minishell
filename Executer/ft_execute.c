/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 15:49:41 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	ft_wait(pid_t pid, int ex)
{
	waitpid(pid, &ex, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	if (WIFEXITED(ex))
	{
		ex = WEXITSTATUS(ex);
	}
	else if (WIFSIGNALED(ex))
	{
		ex = 128 + WTERMSIG(ex);
	}
	return (ex);
}

int	ft_sub_builtins(t_node *root, int *pfd)
{
	int	exit_status;

	exit_status = 0;
	g_neobash.last_child = fork();
	if (!g_neobash.last_child)
	{
		exit_status = ex_cmd(root, pfd);
		exit(exit_status);
	}
	else
		return (ft_wait(g_neobash.last_child, exit_status));
}

int	ft_executer(t_node *root, int *pfd)
{
	int	exit_status;

	signal(SIGINT, handler);
	if (!root)
		return (0);
	if (root->type == PIPE_N)
		exit_status = ft_pipes(root);
	else if (root->type == AND_N)
		exit_status = ft_exec_and(root);
	else if (root->type == OR_N)
		exit_status = ft_exec_or(root);
	else
	{
		if (root->is_block == 1 && root->args
			&& is_builtin(*get_cmdagrs(root->args)))
			exit_status = ft_sub_builtins(root, pfd);
		else
			exit_status = ex_cmd(root, pfd);
	}
	return (exit_status);
}

void	execution(void)
{
	if (!g_neobash.tree)
		return ;
	ft_before_exec(g_neobash.tree);
	if (g_neobash.here_dc_ex)
	{
		g_neobash.status = 130;
		g_neobash.here_dc_ex = false;
		return ;
	}
	g_neobash.status = ft_executer(g_neobash.tree, NULL);
	ft_rstds();
}
