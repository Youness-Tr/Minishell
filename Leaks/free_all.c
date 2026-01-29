/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:50:28 by kali              #+#    #+#             */
/*   Updated: 2024/08/15 12:55:55 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	ft_free_all(void)
{
	t_leak	*current;
	t_leak	*next;

	current = g_neobash.leaks;
	while (current != NULL)
	{
		next = current->next;
		free(current->address);
		free(current);
		current = next;
	}
	g_neobash.leaks = NULL;
	rl_clear_history();
}

t_leak	*ft_leaks_lstlast(t_leak *lst)
{
	t_leak	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
