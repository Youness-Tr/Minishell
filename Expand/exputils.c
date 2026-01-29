/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exputils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:43:13 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/15 16:43:04 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*handle_squotes(char *str, int *i)
{
	int	start;

	start = *i;
	if (!str)
		return (NULL);
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquotes(char *str, int *i)
{
	char	*res;
	char	quote;

	quote = str[*i];
	res = ft_strdup("\"");
	(*i)++;
	while (str[*i] != quote)
	{
		if (str[*i] == '$')
			res = ft_strjoin(res, handle_dollar(str, i));
		else
			res = ft_strjoin(res, dquote_str(str, i));
	}
	(*i)++;
	return (ft_strjoin(res, "\""));
}

char	*dollar_parse(char *str, int *i)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_neobash.status));
	}
	else if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (normal_str(str, i));
	}
	else if (str[*i] == '$')
	{
		(*i)++;
		return (ft_substr(str, *i - 2, 2));
	}
	else if (!str[*i])
		return (&str[(*i) - 1]);
	return (NULL);
}

char	*handle_dollar(char *str, int *i)
{
	int		start;
	char	*var;
	char	*value;

	(*i)++;
	var = dollar_parse(str, i);
	if (var)
		return (var);
	if (!valid_char(str[*i]))
		return (ft_strdup(""));
	start = *i;
	while (valid_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = get_env_val(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*normal_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
