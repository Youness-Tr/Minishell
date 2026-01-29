/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:43:22 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/15 16:41:02 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

char	*ft_expand(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			res = ft_strjoin(res, handle_squotes(str, &i));
		else if (str[i] == '"' || str[i] == '`')
			res = ft_strjoin(res, handle_dquotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin(res, handle_dollar(str, &i));
		else
			res = ft_strjoin(res, normal_str(str, &i));
	}
	return (res);
}
