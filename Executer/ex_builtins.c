/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:47:38 by kali              #+#    #+#             */
/*   Updated: 2024/08/15 16:55:53 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

bool	is_builtin(char *str)
{
	if (!str || !str[0])
		return (false);
	if (!ft_strcmp(str, "cd"))
		return (true);
	if (!ft_strcmp(str, "env"))
		return (true);
	if (!ft_strcmp(str, "exit"))
		return (true);
	if (!ft_strcmp(str, "pwd"))
		return (true);
	if (!ft_strcmp(str, "unset"))
		return (true);
	if (!ft_strcmp(str, "echo"))
		return (true);
	if (!ft_strcmp(str, "export"))
		return (true);
	else
		return (false);
}

int	ft_strcmpv(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 == '\'' || *s1 == '"')
			s1++;
		else if (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	return ((int)*s1 - (int)*s2);
}

int	ex_builtins(t_node *root)
{
	char	**arg;

	arg = get_astiriskargs(root->args);
	if (!ft_strcmp(g_neobash.argss[0], "cd"))
		return (bt_cd(g_neobash.argss));
	if (!ft_strcmp(g_neobash.argss[0], "env"))
		return (ft_env(g_neobash.envl), 0);
	if (!ft_strcmp(g_neobash.argss[0], "exit"))
	{
		ft_exit(g_neobash.argss);
		return (g_neobash.status);
	}
	if (!ft_strcmp(g_neobash.argss[0], "pwd"))
		return (ft_pwd(g_neobash.argss));
	if (!ft_strcmp(g_neobash.argss[0], "unset"))
		return (ft_unset(g_neobash.argss), 0);
	if (!ft_strcmp(g_neobash.argss[0], "echo"))
		return (ft_echo(ft_astirisk(root) + ft_strlen(arg[0]), false, false),
			0);
	if (!ft_strcmp(g_neobash.argss[0], "export"))
		return (ft_export(ft_astirisk(root) + ft_strlen(arg[0])));
	else
		return (1);
}
