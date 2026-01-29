/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astirisk_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:53:56 by kali              #+#    #+#             */
/*   Updated: 2024/08/15 11:39:01 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*ft_norm(char *line, char *str, int *i)
{
	int		start;
	char	q;

	q = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != q)
		(*i)++;
	str = ft_strjoin(str, ft_substr(line, start, *i - start + 1));
	if (!line[*i])
		return (str);
	(*i)++;
	return (str);
}

static void	ft_tool(char *line, int *i, int *nargs, char **res)
{
	char	*str;
	int		start;

	str = ft_strdup("");
	while (line[*i] == '\"' || line[*i] == '\'')
	{
		str = ft_norm(line, str, i);
		if (line[*i] && line[*i] != ' ')
		{
			start = *i;
			while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\"'
				&& line[*i] != '\'')
				(*i)++;
			str = ft_strjoin(str, ft_substr(line, start, *i - start));
		}
	}
	res[*nargs] = str;
}

static void	ft_trem(char *line, int *i, int *nargs, char **res)
{
	char	*str;
	int		start;

	str = ft_strdup("");
	while (line[*i] && !ft_isspace(line[*i]))
	{
		start = *i;
		while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\"'
			&& line[*i] != '\'')
			(*i)++;
		str = ft_strjoin(str, ft_substr(line, start, *i - start));
		if (line[*i] == '\"' || line[*i] == '\'')
			str = ft_norm(line, str, i);
	}
	res[*nargs] = str;
}

char	**get_astiriskargs(char *line)
{
	char	**res;
	int		i;
	int		nargs;

	i = 0;
	nargs = 0;
	res = NULL;
	if (!line || !line[0])
		return (NULL);
	res = ft_malloc(sizeof(char *) * (ft_strlen(line) + 1));
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		if (line[i] == '\'' || line[i] == '"')
			ft_tool(line, &i, &nargs, res);
		else
			ft_trem(line, &i, &nargs, res);
		nargs++;
	}
	res[nargs] = NULL;
	return (res);
}
