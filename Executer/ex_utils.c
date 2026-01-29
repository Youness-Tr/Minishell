/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:58:23 by kali              #+#    #+#             */
/*   Updated: 2024/08/14 17:28:46 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

static void	ft_tool(char *line, int *i, int *nargs, char **res)
{
	char	*str;
	int		start;

	str = ft_strdup("");
	while (line[*i] == '\"' || line[*i] == '\'')
	{
		str = ft_mron(line, str, i);
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

void	ft_trem(char *line, int *i, int *nargs, char **res)
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
		{
			str = ft_mron(line, str, i);
		}
	}
	res[*nargs] = str;
}

char	**get_cmdagrs(char *line)
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

char	**get_my_envp(void)
{
	int		i;
	char	**res;
	t_env	*tmpl;
	int		lsize;

	lsize = ft_lstsizev2(g_neobash.envl) + 1;
	res = ft_malloc(sizeof(char *) * lsize);
	i = 0;
	tmpl = g_neobash.envl;
	while (tmpl)
	{
		res[i] = ft_strjoinc(tmpl->key, tmpl->value, '=');
		i++;
		tmpl = tmpl->next;
	}
	res[i] = NULL;
	return (res);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	if (!paths)
		return (NULL);
	while (*paths)
	{
		g_neobash.tmp = ft_strjoin(*paths, "/");
		g_neobash.palestine = ft_strjoin(g_neobash.tmp, cmd);
		if (access(g_neobash.palestine, X_OK) == 0)
			return (g_neobash.palestine);
		paths++;
	}
	return (NULL);
}
