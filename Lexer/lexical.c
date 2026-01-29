/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:16:25 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 17:00:36 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	ft_err(char *err, int flag)
{
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	if (!flag)
		exit(1);
}

bool	ft_check_synx(bool error, char qt)
{
	if (error == true && qt == '\'')
	{
		g_neobash.status = 2;
		return (ft_err("g_neobash: syntax error near unexpected token `''", 1),
			false);
	}
	if (error == true && qt == '"')
	{
		g_neobash.status = 2;
		return (ft_err("g_neobash: syntax error near unexpected token `\"'", 1),
			false);
	}
	return (true);
}

bool	ft_coutquotes(void)
{
	int		i;
	char	qt;
	bool	error;

	i = 0;
	error = false;
	while (g_neobash.line[i])
	{
		if (g_neobash.line[i] == '"' || g_neobash.line[i] == '\'')
		{
			qt = g_neobash.line[i];
			i++;
			while (g_neobash.line[i] && g_neobash.line[i] != qt)
				i++;
			if (g_neobash.line[i] == qt)
				error = false;
			else
				error = true;
			if (!g_neobash.line[i])
				break ;
		}
		i++;
	}
	return (ft_check_synx(error, qt));
}

void	give_token(void)
{
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (g_neobash.sub[i])
	{
		if (is_whitespaces(*g_neobash.sub[i]))
			i++;
		if (!g_neobash.sub[i])
			break ;
		ft_lstadd_backv3(&head, ft_lstnewv3(g_neobash.sub[i], set_token(i)));
		i++;
	}
	g_neobash.tokens = head;
}

void	ft_lexer(void)
{
	ft_lexical(0);
	give_token();
}
