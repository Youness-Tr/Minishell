/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:29:31 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 11:41:31 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*ft_mron(char *line, char *str, int *i)
{
	int		start;
	char	q;

	q = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != q)
		(*i)++;
	str = ft_strjoin(str, ft_substr(line, start, *i - start));
	if (!line[*i])
		return (str);
	(*i)++;
	return (str);
}

void	handle_(void)
{
	int	x;

	x = count_args(g_neobash.argss);
	if (x > 0)
		update_env("_", g_neobash.argss[x - 1]);
	else
		update_env("_", g_neobash.argss[x]);
}
