/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:42:59 by kali              #+#    #+#             */
/*   Updated: 2024/08/14 19:11:46 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

static void	ft_tools(t_io *io)
{
	pid_t	pid;

	pipe(g_neobash.fd);
	io->here_doc = g_neobash.fd[0];
	pid = fork();
	if (pid == 0)
	{
		close(g_neobash.fd[0]);
		heredoc_f(io, g_neobash.fd);
	}
	else
	{
		close(g_neobash.fd[1]);
		g_neobash.status = ft_wait(pid, g_neobash.status);
		if (g_neobash.status)
			g_neobash.here_dc_ex = true;
		io->here_doc = g_neobash.fd[0];
	}
}

char	*join_args(char **s)
{
	int		i;
	char	*res;

	i = 0;
	if (!*s || !*s[0])
		return (NULL);
	res = ft_strdup("");
	while (s[i])
	{
		res = ft_strjoinc(res, s[i], ' ');
		i++;
	}
	return (res);
}

// root->exp_val dyal node

void	ft_init_io(t_node *root)
{
	t_io	*io;

	if (!root)
		return ;
	io = root->iol;
	while (io)
	{
		if (io->type == HERE_DOC)
		{
			ft_tools(io);
		}
		else
		{
			io->exp_val = ft_expand(io->value);
			g_neobash.argss = get_cmdagrs(io->exp_val);
			if (g_neobash.argss)
				io->exp_val = join_args(g_neobash.argss);
			io->exp_val = ft_strtrim(asterisk(io->exp_val), " ");
		}
		io = io->next;
	}
}

static int	ft_hanadle(t_io *tmp_io, int flag)
{
	int	ex;

	ex = 0;
	if (tmp_io->type == OUT)
	{
		ex = ft_out(tmp_io, flag);
		if (ex)
			return (ex);
	}
	else if (tmp_io->type == IN)
	{
		ex = ft_in(tmp_io, flag);
		if (ex)
			return (ex);
	}
	else if (tmp_io->type == APP)
	{
		ex = ft_app(tmp_io, flag);
		if (ex)
			return (ex);
	}
	return (ex);
}

int	ft_io(t_node *root, int flag)
{
	t_io	*tmp_io;
	int		ex;

	tmp_io = root->iol;
	ex = 0;
	while (tmp_io)
	{
		ex = ft_hanadle(tmp_io, flag);
		if (ex)
			return (ex);
		else if (tmp_io->type == HERE_DOC)
		{
			if (dup2(tmp_io->here_doc, STDIN_FILENO) == -1)
			{
				perror("dup2");
				return (1);
			}
			close(tmp_io->here_doc);
		}
		tmp_io = tmp_io->next;
	}
	return (0);
}
