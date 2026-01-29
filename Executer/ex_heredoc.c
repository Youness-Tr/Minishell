/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:39:40 by kali              #+#    #+#             */
/*   Updated: 2024/08/15 09:14:53 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

bool	ft_is_delimiter(char *delimiter, char *str)
{
	int		i;
	char	**res;

	i = 0;
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
		g_neobash.exp_here = false;
	res = get_cmdagrs(delimiter);
	while (*str && res[0][i])
	{
		if (*str == res[0][i])
		{
			str++;
			i++;
		}
		else
			return (false);
	}
	return (!res[0][i] && !*str);
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_neobash.status = 130;
		ft_putstr_fd("\n", 1);
		exit(130);
	}
}

void	heredoc_f(t_io *io, int fd[2])
{
	char	*line;

	signal(SIGINT, heredoc_handler);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			break ;
		}
		if (ft_is_delimiter(io->value, line))
		{
			free(line);
			break ;
		}
		if (g_neobash.exp_here == true)
			ft_putstr_fd(expand_heredoc(line), fd[1]);
		else
			ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
	exit(0);
}
