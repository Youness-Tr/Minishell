/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_hand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:28:51 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/14 08:51:53 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

bool	ft_argv(char **cmd)
{
	if (g_neobash.prs_state)
		return (NULL);
	if (!*cmd)
		*cmd = ft_strdup("");
	if (!*cmd)
		return (NULL);
	while (g_neobash.cur_tok && g_neobash.cur_tok->type == WRD)
	{
		*cmd = ft_strjoinc(*cmd, g_neobash.cur_tok->value, ' ');
		if (!*cmd)
			return (set_state(2), false);
		ft_skip_tok();
	}
	return (true);
}

t_node	*ft_scmd(void)
{
	t_node	*result;

	if (g_neobash.prs_state)
		return (NULL);
	result = ft_newnode(CMD_N);
	if (!result)
		return (set_state(2), NULL);
	while (g_neobash.cur_tok && (g_neobash.cur_tok->type == WRD || is_io()))
	{
		if (g_neobash.cur_tok->type == WRD)
		{
			if (!ft_argv(&result->args))
				return (set_state(2), NULL);
		}
		else if (is_io())
		{
			if (!create_iol(&result->iol, get_type(g_neobash.cur_tok->type)))
				return (free(result->args), free(result), NULL);
		}
	}
	return (result);
}

static void	ft_tool(t_node *result)
{
	t_node	*tmp;

	if (g_neobash.cur_tok && !is_pair())
	{
		tmp = ft_rdp(5);
		if (tmp)
			result->iol = tmp->iol;
	}
}

t_node	*ft_left_hand(void)
{
	t_node	*result;

	if (g_neobash.prs_state || !g_neobash.cur_tok)
		return (NULL);
	if (is_pair())
		return (set_state(1), NULL);
	else if (g_neobash.cur_tok->type == L_PARENT)
	{
		ft_skip_tok();
		result = ft_rdp(0);
		if (!result)
			return (set_state(2), NULL);
		if (!g_neobash.cur_tok || g_neobash.cur_tok->type != R_PARENT)
			return (set_state(1), NULL);
		ft_skip_tok();
		ft_tool(result);
		result->is_block = true;
		return (result);
	}
	else
		return (ft_scmd());
}
