/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:36:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/08/15 15:23:46 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	param(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == '\'' || s[i] == '"')
		i++;
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i] == 'n' || s[i] == '"' || s[i] == '\'')
	{
		i++;
	}
	if (s[i] == '\0' || s[i] == ' ')
		return (i);
	return (0);
}

static int	skipsq(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (ft_isspace(s[i])))
		i++;
	if (!s[i])
		return (ft_putstr_fd("\n", 1), 0);
	return (i);
}

void	ft_echo(char *s, bool sq, bool dq)
{
	bool	nl;
	int		i;

	nl = true;
	i = skipsq(s);
	while (param(&s[i]))
	{
		nl = false;
		i += param(&s[i]);
		i += skip(&s[i]);
	}
	if (i == 0)
		return ;
	while (s[i])
	{
		if (s[i] == '\"' && !sq)
			dq = !dq;
		else if (s[i] == '\'' && !dq)
			sq = !sq;
		else
			printf("%c", s[i]);
		i++;
	}
	if (nl)
		printf("\n");
}
