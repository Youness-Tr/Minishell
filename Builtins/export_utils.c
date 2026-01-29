/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:59:15 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/14 16:34:34 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	print_ex(t_env *env)
{
	t_env	*env_dup;

	g_neobash.envl_dup = env_list_dup(env);
	env_dup = g_neobash.envl_dup;
	if (!env_dup)
	{
		printf("Failed to duplicate environment list.\n");
		return ;
	}
	sort_env(env_dup);
	while (env_dup)
	{
		printf("declare -x %s", env_dup->key);
		if (env_dup->value && env_dup->value[0])
			printf("=\"%s\"\n", env_dup->value);
		else
			printf("\n");
		env_dup = env_dup->next;
	}
}

t_env	*dup_env(t_env *env)
{
	t_env	*new_node;

	new_node = ft_malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = strdup(env->key);
	new_node->value = NULL;
	if (env->value)
		new_node->value = ft_strdup(env->value);
	new_node->next = NULL;
	return (new_node);
}

t_env	*env_list_dup(t_env *env)
{
	t_env	*new_head;
	t_env	*new_tail;
	t_env	*new_node;

	new_head = NULL;
	new_tail = NULL;
	while (env)
	{
		new_node = dup_env(env);
		if (!new_head)
		{
			new_head = new_node;
			new_tail = new_node;
		}
		else
		{
			new_tail->next = new_node;
			new_tail = new_node;
		}
		env = env->next;
	}
	return (new_head);
}

static void	ft_swap(t_env *a, t_env *b, int *swapped)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
	*swapped = 1;
}

void	sort_env(t_env *env)
{
	t_env	*tmp;
	t_env	*p;
	t_env	*d;
	int		swapped;

	tmp = env;
	if (!tmp)
		return ;
	while (1)
	{
		swapped = 0;
		p = tmp;
		while (p->next)
		{
			d = p->next;
			if (ft_strcmp(p->key, d->key) > 0)
				ft_swap(p, d, &swapped);
			p = p->next;
		}
		if (!swapped)
			break ;
	}
}
