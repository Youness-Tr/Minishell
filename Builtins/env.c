/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:36:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/14 11:21:12 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

t_env	*ft_env_lstnew(char *var)
{
	t_env	*lst;
	int		len;

	lst = (t_env *)ft_malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = ft_malloc(ft_strlenc(var, '='));
	ft_strcpy(lst->key, var, '=');
	len = ft_strlen(lst->key);
	lst->value = ft_malloc(ft_strlenc((var + len), '\0'));
	ft_strcpy(lst->value, var + len + 1, '\0');
	lst->visible = true;
	lst->next = NULL;
	return (lst);
}

t_env	*ft_env_lstlast(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_env_lstadd_back(t_env **lst, t_env *newx)
{
	t_env	*node;

	if (!lst || !newx)
		return ;
	node = ft_env_lstlast(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}

void	get_env_list(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		ft_env_lstadd_back(&g_neobash.envl, ft_env_lstnew(env[i]));
		i++;
	}
}

void	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->visible == true)
		{
			printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
