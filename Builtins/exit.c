/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:01 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 15:03:44 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	skip_zero(char *str)
{
	while (*str == '0')
		str++;
	return ;
}

int	is_positive(char *str)
{
	const char	*limit = "9223372036854775807";
	int			len;

	len = 0;
	skip_zero(str);
	if (*str == '+')
		str++;
	len = ft_strlen(str);
	if (len > 19)
		return (1);
	if (len == 19 && (ft_strcmp(str, limit) > 0))
		return (1);
	return (0);
}

int	is_negative(char *s)
{
	char	*neg;
	int		len;

	neg = "-9223372036854775808";
	len = ft_strlen(s);
	if (*s == '-')
	{
		len -= 1;
		if (len > 19)
			return (1);
		if (len == 19 && ft_strcmp(s, neg) > 0)
			return (1);
	}
	return (0);
}

int	out_of_range(char *str)
{
	if (*str == '-')
		return (is_negative(str));
	return (is_positive(str));
}

void	ft_exit(char **str)
{
	int	i;
	int	c;

	i = 0;
	c = 1;
	if (str && str[c] && (str[c][0] == '-' || str[c][0] == '+'))
		i++;
	if (exit_parse(str, &i, &c))
	{
		g_neobash.status = 1;
		return ;
	}
	if (!str[c][i])
		g_neobash.status = ft_atoi(str[c]);
	if (out_of_range(str[c]))
	{
		ft_putstr_fd("exit\n", 1);
		ft_free_all();
		exit(2);
	}
	ft_free_all();
	exit(g_neobash.status);
}
