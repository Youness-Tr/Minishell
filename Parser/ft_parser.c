/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:58:34 by kali              #+#    #+#             */
/*   Updated: 2024/08/11 20:47:09 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	ft_precedence(t_token_t tp)
{
	if (tp == PIPE)
		return (2);
	else if (tp == OR)
		return (1);
	else if (tp == AND)
		return (0);
	else
		return (-1);
}

t_root_t	get_node_t(t_token_t tk)
{
	if (tk == PIPE)
		return (PIPE_N);
	else if (tk == AND)
		return (AND_N);
	else if (tk == OR)
		return (OR_N);
	return (NOTHING);
}

t_node	*create_pair_node(t_node *left, t_node *right, t_root_t node_t)
{
	t_node	*root;

	root = ft_newnode(node_t);
	root->left = left;
	root->right = right;
	return (root);
}

t_node	*ft_rdp(int p)
{
	t_node		*left;
	t_node		*right;
	t_token_t	tmp;

	if (g_neobash.prs_state)
		return (NULL);
	left = ft_left_hand();
	if (!left)
		return (NULL);
	while (is_pair() && ft_precedence(g_neobash.cur_tok->type) >= p)
	{
		tmp = g_neobash.cur_tok->type;
		ft_skip_tok();
		if (!g_neobash.cur_tok)
			return (set_state(1), left);
		g_neobash.np = ft_precedence(tmp) + 1;
		right = ft_rdp(g_neobash.np);
		if (!right)
			return (left);
		left = create_pair_node(left, right, get_node_t(tmp));
		if (!left)
			return (NULL);
	}
	return (left);
}

t_node	*ft_parser(void)
{
	t_node	*tree_root;

	g_neobash.cur_tok = g_neobash.tokens;
	tree_root = ft_rdp(0);
	if (g_neobash.cur_tok)
		return (set_state(1), tree_root);
	return (tree_root);
}
