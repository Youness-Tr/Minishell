/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 06:26:32 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 13:03:12 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

t_token	*ft_lstlastv3(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_token	*ft_lstnewv3(char *var, t_token_t token)
{
	t_token	*lst;

	lst = (t_token *)ft_malloc(sizeof(t_token));
	if (!lst)
		return (NULL);
	lst->value = ft_strdup(var);
	lst->type = token;
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_backv3(t_token **lst, t_token *newx)
{
	t_token	*node;

	if (!lst || !newx)
		return ;
	node = ft_lstlastv3(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}

bool	ft_check_io_pairs(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
		return (true);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (true);
	else if (line[i] == '|' && line[i + 1] == '|')
		return (true);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (true);
	else
		return (false);
}

bool	check_spcial(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (false);
	if (c >= '0' && c <= '9')
		return (false);
	if (c == '-' || c == '.' || c == '/' || c == '$' || c == '_' || c == '?'
		|| c == '=' || c == '*' || c == '"' || c == '+' || c == '\''
		|| c == '^')
		return (false);
	return (true);
}
