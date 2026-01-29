/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/15 16:55:02 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

t_env	*search_envl(char *s)
{
	t_env	*env;
	t_env	*tmp;

	env = g_neobash.envl;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(s, tmp->key, ft_strlen(s)))
			return (tmp);
		tmp = tmp->next;
	}
	tmp = env;
	return (NULL);
}

int	option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '-')
		{
			printf("bash: pwd: '%s': invalid option\n", &str[i]);
			g_neobash.status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_pwd(char **s)
{
	char	*path;
	int		c;

	c = 1;
	path = NULL;
	if (option(s[c]))
		return (2);
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	return (0);
}
