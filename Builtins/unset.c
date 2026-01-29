/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:35:31 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/15 16:55:35 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

static void	iter(char **s, t_env *tmp, t_env *prev)
{
	int	i;

	while (tmp)
	{
		i = 1;
		while (s[i] && tmp->next)
		{
			if (!ft_strcmp(s[i], tmp->key) && ft_strcmp(s[i], "_"))
			{
				if (prev)
					prev->next = tmp->next;
				else
				{
					prev = tmp->next;
					g_neobash.envl = tmp->next;
				}
				tmp = prev;
				break ;
			}
			i++;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(char **s)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_neobash.envl;
	prev = NULL;
	if (!s[1])
		return ;
	iter(s, tmp, prev);
}
