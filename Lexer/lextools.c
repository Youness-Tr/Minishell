/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lextools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:20:20 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 16:57:39 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

bool	is_whitespaces(char line)
{
	if (line == ' ' || line == '\t' || line == '\v')
		return (true);
	return (false);
}

static void	sub_quotition(int *i, int *ntoken)
{
	int	start;
	int	len;

	start = *i;
	len = count_inside_quotes(*i, g_neobash.line[*i]);
	g_neobash.sub[*ntoken] = ft_substr(g_neobash.line, start, len - start);
	(*ntoken)++;
	(*i) = len;
}

static void	sub_spcial(int *i, int *ntoken)
{
	int	len;

	len = 0;
	if (is_whitespaces(g_neobash.line[*i]))
	{
		len = count_whitespaces(g_neobash.line, *i);
		g_neobash.sub[*ntoken] = ft_substr(g_neobash.line, *i, len);
		(*i) += len;
	}
	else if (ft_check_io_pairs(g_neobash.line, *i))
	{
		g_neobash.sub[*ntoken] = ft_substr(g_neobash.line, *i, 2);
		(*i) += 2;
	}
	else
	{
		g_neobash.sub[*ntoken] = ft_substr(g_neobash.line, *i, 1);
		(*i)++;
	}
	(*ntoken)++;
}

static void	sub_other(int *i, int *ntoken)
{
	int	start;

	start = *i;
	while (!check_spcial(g_neobash.line[*i]))
		(*i)++;
	g_neobash.sub[*ntoken] = ft_substr(g_neobash.line, start, *i - start);
	(*ntoken)++;
}

void	ft_lexical(int ntoken)
{
	int	i;

	i = 0;
	g_neobash.sub = ft_malloc(sizeof(char *) * (ft_strlen(g_neobash.line) + 1));
	while (g_neobash.line[i])
	{
		if (is_quotition(g_neobash.line[i]))
			sub_quotition(&i, &ntoken);
		else if (check_spcial(g_neobash.line[i]))
			sub_spcial(&i, &ntoken);
		else
			sub_other(&i, &ntoken);
	}
	g_neobash.sub[ntoken] = NULL;
}
