/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:05:43 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/15 10:38:40 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*get_env_val(char *key)
{
	t_env	*envlst;

	envlst = g_neobash.envl;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	update_env(char *key, char *value)
{
	t_env	*envlst;

	envlst = g_neobash.envl;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
			{
				envlst->value = ft_strdup(value);
				envlst->visible = true;
			}
			return ;
		}
		envlst = envlst->next;
	}
}

t_env	*exp_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!value)
	{
		new->value = ft_strdup("");
		new->visible = false;
	}
	else
	{
		new->value = ft_strdup(value);
		new->visible = true;
	}
	new->next = NULL;
	return (new);
}

void	exp_back(t_env *new)
{
	t_env	*curr;

	if (!g_neobash.envl)
	{
		g_neobash.envl = new;
		return ;
	}
	curr = g_neobash.envl;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}
