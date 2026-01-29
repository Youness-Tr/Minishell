/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:16:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/13 22:22:20 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

bool	ft_check_tk(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '>' && line[i + 1] == '>')
		return (true);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (true);
	else if (line[i] == '|' && line[i + 1] == '|')
		return (true);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (true);
	else
		return (false);
}

bool	ft_check_tkv2(char c)
{
	if (c == '>')
		return (true);
	else if (c == '<')
		return (true);
	else if (c == '|')
		return (true);
	else if (c == '(')
		return (true);
	else if (c == ')')
		return (true);
	else
		return (false);
}

int	count_inside_quotes(int i, char q)
{
	while (g_neobash.line[i] && (g_neobash.line[i] == '\''
			|| g_neobash.line[i] == '"'))
	{
		q = g_neobash.line[i];
		i++;
		while (g_neobash.line[i] && g_neobash.line[i] != q)
			i++;
		if (g_neobash.line[i] == q)
			i++;
		if (g_neobash.line[i] && g_neobash.line[i] != ' '
			&& !ft_check_tk(&g_neobash.line[i])
			&& !ft_check_tkv2(g_neobash.line[i]))
		{
			while (g_neobash.line[i] && !ft_isspace(g_neobash.line[i]))
				i++;
		}
		else
			break ;
	}
	return (i);
}

int	count_whitespaces(char *line, int i)
{
	int	count;

	count = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
	{
		i++;
		count += 1;
	}
	return (count);
}

t_token_t	set_token(int i)
{
	if (!ft_strcmp(g_neobash.sub[i], ">"))
		return (REDIRECT);
	else if (!ft_strcmp(g_neobash.sub[i], "<"))
		return (INPUT);
	else if (!ft_strcmp(g_neobash.sub[i], ">>"))
		return (APPEND);
	else if (!ft_strcmp(g_neobash.sub[i], "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(g_neobash.sub[i], "&&"))
		return (AND);
	else if (!ft_strcmp(g_neobash.sub[i], "||"))
		return (OR);
	else if (!ft_strcmp(g_neobash.sub[i], "|"))
		return (PIPE);
	else if (!ft_strcmp(g_neobash.sub[i], "("))
		return (L_PARENT);
	else if (!ft_strcmp(g_neobash.sub[i], ")"))
		return (R_PARENT);
	else if (is_badchar(g_neobash.sub[i]))
		return (SYNTAX);
	else
		return (WRD);
}
