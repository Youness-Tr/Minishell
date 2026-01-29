/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:58:48 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/14 16:17:14 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*get_key(char *str)
{
	int	i;

	i = 0;
	g_neobash.count = 0;
	g_neobash.app = false;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "+=", 2))
		{
			g_neobash.app = true;
			g_neobash.count = i + 2;
			return (ft_substr(str, 0, i));
		}
		else if (str[i] == '=' || str[i] == ' ')
		{
			g_neobash.count = i + 1;
			return (ft_substr(str, 0, i));
		}
		i++;
	}
	g_neobash.count = i;
	return (ft_strdup(str));
}

char	*sub_value(char *str)
{
	int		i;
	int		s;
	char	*res;

	i = 0;
	s = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '=')
		{
			s = i + 1;
			if (!str[s])
				return (ft_strdup(""));
			res = handle_quote(str, s);
			return (res);
		}
		i++;
	}
	return (NULL);
}

void	set_var(char *s, int *i)
{
	char	*key;
	char	*ss;
	char	*app;

	key = get_key(&s[*i]);
	if (search_env(key))
	{
		if (g_neobash.app == true)
		{
			app = ft_strjoin(get_env_val(key), sub_value(&s[*i]));
			update_env(key, app);
		}
		else
			update_env(key, sub_value(&s[*i]));
	}
	else
	{
		ss = sub_value(&s[*i]);
		exp_back(exp_new(key, ss));
	}
}

int	ft_export(char *s)
{
	int	i;

	i = 0;
	i = skip(s);
	if (!(s[i]))
	{
		print_ex(g_neobash.envl);
		return (1);
	}
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i++;
		if (parse_key(&s[i]))
		{
			ft_error("bash: export: `$': not a valid identifier", &s[i]);
			return (1);
		}
		else
			set_var(s, &i);
		i += g_neobash.count;
	}
	return (0);
}
