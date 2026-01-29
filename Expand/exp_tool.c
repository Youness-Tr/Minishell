/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:43:13 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/14 22:30:09 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

bool	valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*dquote_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
