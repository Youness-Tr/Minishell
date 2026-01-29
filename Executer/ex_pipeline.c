/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:05:33 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 16:56:25 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	run_io(t_node *root)
{
	int	exit_status;

	exit_status = 0;
	if (root->iol)
	{
		ft_init_io(root);
		exit_status = ft_io(root, 0);
		if (exit_status)
			return (exit_status);
	}
	return (exit_status);
}

int	ft_pipes(t_node *root)
{
	int	exit_status;

	exit_status = 0;
	exit_status = run_io(root);
	if (exit_status)
		return (exit_status);
	if (root->is_block == 1)
	{
		exit_status = run_io(root);
		if (exit_status)
			return (exit_status);
		g_neobash.last_child = fork();
		if (!g_neobash.last_child)
		{
			exit_status = ex_pipes(root);
			while (waitpid(-1, NULL, 0) != -1)
				;
			exit(exit_status);
		}
		else
			return (ft_wait(g_neobash.last_child, exit_status));
	}
	else
		return (ex_pipes(root));
}
