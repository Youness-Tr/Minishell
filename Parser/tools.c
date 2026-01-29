/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:57 by kali              #+#    #+#             */
/*   Updated: 2024/08/11 19:38:13 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	set_state(int state)
{
	g_neobash.prs_state = state;
}

void	ft_skip_tok(void)
{
	g_neobash.cur_tok = g_neobash.cur_tok->next;
}

bool	is_pair(void)
{
	if (!g_neobash.cur_tok)
		return (false);
	if (g_neobash.cur_tok->type == OR || g_neobash.cur_tok->type == AND
		|| g_neobash.cur_tok->type == PIPE)
		return (true);
	else
		return (false);
}

bool	is_io(void)
{
	if (!g_neobash.cur_tok)
		return (false);
	if (g_neobash.cur_tok->type == APPEND || g_neobash.cur_tok->type == REDIRECT
		|| g_neobash.cur_tok->type == INPUT
		|| g_neobash.cur_tok->type == HEREDOC)
		return (true);
	else
		return (false);
}

t_node	*ft_newnode(t_root_t node_t)
{
	t_node	*res;

	res = ft_malloc(sizeof(t_node));
	res->type = node_t;
	res->args = NULL;
	res->left = NULL;
	res->right = NULL;
	res->iol = NULL;
	res->is_block = false;
	return (res);
}
