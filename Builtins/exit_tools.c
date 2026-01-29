/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:13:44 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 14:59:57 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	exit_parse(char **str, int *i, int *c)
{
	if (g_neobash.level > 1)
	{
		g_neobash.level -= 1;
		update_env("SHLVL", ft_itoa(g_neobash.level));
	}
	if (count_args(str) == 1)
		return (ft_putstr_fd("exit\n", 1), exit(g_neobash.status), 0);
	if (count_args(str) > 2)
	{
		ft_error("exit\ng_neobash: exit: too many arguments", NULL);
		g_neobash.status = 1;
		return (1);
	}
	while (str[*c][*i])
	{
		if (ft_isdigit(str[*c][*i]))
			(*i)++;
		else
		{
			ft_error("exit: numeric argument required", NULL);
			g_neobash.status = 2;
			break ;
		}
	}
	return (0);
}
