/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:52:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 15:48:17 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	ft_lstsizev2(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_close_pfds(int *pfd)
{
	if (pfd)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
}

void	ft_rstds(void)
{
	dup2(g_neobash.in, 0);
	dup2(g_neobash.out, 1);
}

void	ft_before_exec(t_node *root)
{
	t_root_t	tp;

	if (!root)
		return ;
	tp = root->type;
	if (tp == PIPE_N || tp == OR_N || tp == AND_N)
	{
		ft_before_exec(root->left);
		ft_before_exec(root->right);
	}
	else
		ft_init_io(root);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_neobash.status = 130;
	}
}
