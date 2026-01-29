/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:20:38 by kali              #+#    #+#             */
/*   Updated: 2024/08/15 10:52:01 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

static int	sub_or(t_node *root)
{
	int	exit_status;

	exit_status = 0;
	exit_status = run_io(root);
	if (exit_status)
		return (exit_status);
	g_neobash.last_child = fork();
	if (!g_neobash.last_child)
	{
		exit_status = ft_executer(root->left, NULL);
		g_neobash.status = exit_status;
		while (waitpid(-1, NULL, 0) != -1)
			;
		if (exit_status)
			exit_status = ft_executer(root->right, NULL);
		exit(exit_status);
	}
	else
		return (ft_wait(g_neobash.last_child, exit_status));
}

int	ft_exec_or(t_node *root)
{
	int	exit_status;

	exit_status = 0;
	if (root->is_block == 1)
	{
		exit_status = sub_or(root);
		g_neobash.status = exit_status;
		return (g_neobash.status);
	}
	else
	{
		exit_status = ft_executer(root->left, NULL);
		g_neobash.status = exit_status;
		if (g_neobash.status)
			exit_status = ft_executer(root->right, NULL);
	}
	return (exit_status);
}
