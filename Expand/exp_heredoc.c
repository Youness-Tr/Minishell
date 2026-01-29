/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:30:48 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/14 20:34:53 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*quote_str(char *str, int *i, char q)
{
	int	start;

	start = *i;
	while (str[*i] != q && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_quotes(char *str, int *i)
{
	char	*res;
	char	quote;
	char	*qq;

	quote = str[*i];
	if (quote == '\'')
		qq = ft_strdup("\'");
	else if (quote == '\"')
		qq = ft_strdup("\"");
	res = ft_strjoin(ft_strdup(""), qq);
	(*i)++;
	while (str[*i] != quote)
	{
		if (str[*i] == '$')
			res = ft_strjoin(res, handle_dollar(str, i));
		else
			res = ft_strjoin(res, quote_str(str, i, quote));
	}
	(*i)++;
	return (ft_strjoin(res, qq));
}

char	*expand_heredoc(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '`' || str[i] == '\'')
			res = ft_strjoin(res, handle_quotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin(res, handle_dollar(str, &i));
		else
			res = ft_strjoin(res, normal_str(str, &i));
	}
	return (res);
}
