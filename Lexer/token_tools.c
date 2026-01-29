/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:14:57 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/13 22:22:16 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

bool	is_badchar(char *c)
{
	if (c[0] == ';' || c[0] == '`' || c[0] == '\\')
		return (true);
	if (c[0] == '&' && ft_strlen(c) == 1)
		return (true);
	else
		return (false);
}

bool	is_quotition(char i)
{
	if (i == 34)
		return (true);
	if (i == 39)
		return (true);
	else
		return (false);
}
