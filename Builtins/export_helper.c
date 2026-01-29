/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:54:50 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/14 16:16:12 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*alloc_res(char *line, int start)
{
	char	*res;

	res = ft_malloc(sizeof(char) * (ft_strlen(&line[start]) + 1));
	if (!res)
		return (NULL);
	if (line[start] == '\0')
	{
		res[start] = '\0';
		return (res);
	}
	res = ft_strdup("");
	return (res);
}

int	iter_funq(char *line, char **res, int *start, int *i)
{
	char	quote;

	*res = ft_strjoin(*res, ft_substr(line, *start, *i - *start));
	quote = line[*i];
	(*i)++;
	*start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	*res = ft_strjoin(*res, ft_substr(line, *start, *i - *start - 1));
	*start = *i;
	if (!line[*i])
		return (1);
	return (0);
}

char	*handle_quote(char *line, int start)
{
	char	*res;
	int		i;

	i = start;
	res = alloc_res(line, start);
	while (line[i] && !ft_isspace(line[i]))
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (iter_funq(line, &res, &start, &i))
				break ;
		}
		i++;
		if (!line[i] || ft_isspace(line[i]))
			res = ft_strjoin(res, ft_substr(line, start, i - start));
	}
	if (line[i] == ' ')
		i++;
	g_neobash.count = i;
	return (res);
}

int	parse_key(char *str)
{
	int	i;

	i = 0;
	g_neobash.count = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '"'
		&& str[i] != '\'')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (0);
		else if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

bool	search_env(char *s)
{
	t_env	*env;
	t_env	*tmp;

	env = g_neobash.envl;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(s, tmp->key))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
