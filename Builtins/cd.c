/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:58:07 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/15 12:56:58 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	update_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	return (update_env("PWD", cwd), free(cwd), 0);
}

int	skip(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i])
		return (0);
	return (i);
}

int	count_args(char **s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_home(void)
{
	char	*home;

	home = ft_expand("$HOME");
	if (ft_strlen(home) > 1)
		chdir(home);
	else
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	update_env("OLDPWD", get_env_val("PWD"));
	return (0);
}

int	bt_cd(char **s)
{
	int	c;

	c = 1;
	if (count_args(s) > 2)
		return (ft_error("g_neobash: cd: too many arguments", NULL), 1);
	if (!s[c])
	{
		if (ft_home())
			return (1);
		return (update_pwd(), 0);
	}
	else if (chdir(s[c]) == -1)
	{
		ft_error("cd: No such file or directory", NULL);
		return (1);
	}
	if (get_env_val("PWD") == NULL)
		update_env("OLDPWD", ft_strdup(" "));
	else
		update_env("OLDPWD", get_env_val("PWD"));
	return (update_pwd(), 0);
}
