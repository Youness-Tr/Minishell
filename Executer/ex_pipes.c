/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:54:30 by kali              #+#    #+#             */
/*   Updated: 2024/08/14 11:17:47 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	ex_lpipe(int fd[2], t_node *root)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	g_neobash.status = ft_executer(root, fd);
	exit(g_neobash.status);
}

void	ex_rpipe(int fd[2], t_node *root)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	g_neobash.status = ft_executer(root, fd);
	exit(g_neobash.status);
}

static void	ft_handle(t_node *root, pid_t pid0, int *fd)
{
	pid_t	pid1;

	(void)pid0;
	pid1 = fork();
	if (pid1 < 0)
		return ;
	if (!pid1)
		ex_rpipe(fd, root->right);
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(pid0, &g_neobash.status, 0);
		waitpid(pid1, &g_neobash.status, 0);
		if (WIFEXITED(g_neobash.status))
		{
			g_neobash.status = WEXITSTATUS(g_neobash.status);
		}
		else if (WIFSIGNALED(g_neobash.status))
		{
			g_neobash.status = 128 + WTERMSIG(g_neobash.status);
		}
	}
}

int	ex_pipes(t_node *root)
{
	int		fd[2];
	pid_t	pid0;

	if (pipe(fd))
		return (1);
	pid0 = fork();
	if (pid0 < 0)
		return (1);
	if (!pid0)
		ex_lpipe(fd, root->left);
	else
		ft_handle(root, pid0, fd);
	return (g_neobash.status);
}
