/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtools.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 06:25:47 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/13 22:51:28 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	**grep_paths(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

void	check_f(int flag)
{
	if (!flag)
	{
		ft_error("neobash: syntax error near unexpected token `$'",
			g_neobash.cur_tok->value);
		g_neobash.status = 2;
	}
}

void	ft_syntax_after(void)
{
	int	flag;

	flag = 0;
	if (g_neobash.prs_state == 1)
	{
		if (!g_neobash.cur_tok)
		{
			ft_error("neobash: syntax error near unexpected token `$'",
				"newline");
			g_neobash.status = 2;
			return ;
		}
		if (g_neobash.cur_tok->next)
		{
			ft_error("neobash: syntax error near unexpected token `$'",
				g_neobash.cur_tok->value);
			g_neobash.status = 2;
			g_neobash.prs_state = 0;
			flag = 1;
		}
		check_f(flag);
	}
}

bool	synyax_before(void)
{
	t_token	*tmp;

	tmp = g_neobash.tokens;
	while (tmp)
	{
		if (tmp->type == SYNTAX)
		{
			ft_error("g_neobash: syntax error near unexpected token `$'",
				tmp->value);
			g_neobash.status = 2;
			return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
