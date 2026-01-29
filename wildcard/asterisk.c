/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:37:00 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 16:59:08 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*ft_astirisk(t_node *root)
{
	char	**dp;
	int		i;

	i = 0;
	dp = get_astiriskargs(root->args);
	if (!dp || !*dp)
		return (root->args);
	while (dp[i])
	{
		dp[i] = asterisk(dp[i]);
		i++;
	}
	return (join_args(dp));
}

int	match_pattern(const char *pattern, const char *filename)
{
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			if (*(pattern + 1) == '\0')
				return (1);
			while (*filename)
			{
				if (match_pattern(pattern + 1, filename++))
					return (1);
			}
			return (0);
		}
		else if (*pattern != *filename)
			return (0);
		pattern++;
		filename++;
	}
	if (!*pattern && !*filename)
		return (1);
	return (0);
}

int	asterrisk_tool(char *s, int i)
{
	char	qq;

	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			qq = s[i];
			i++;
			while (s[i] && s[i] != qq)
			{
				if (s[i] == '*')
					return (0);
				i++;
			}
		}
		if (s[i] == '*')
			return (1);
		else if (!s[i])
			return (0);
		i++;
	}
	return (0);
}

char	*asterisk(char *s)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*str;
	char			*res;

	res = ft_strdup("");
	if (!asterrisk_tool(s, 0))
		return (s);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	str = join_args(get_cmdagrs(s));
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(str, entry->d_name))
			res = ft_strjoinc(res, entry->d_name, ' ');
		entry = readdir(dir);
	}
	closedir(dir);
	if (!res[0])
		return (s);
	return (res);
}
