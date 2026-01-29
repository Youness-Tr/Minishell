/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:33:47 by kali              #+#    #+#             */
/*   Updated: 2024/08/15 11:24:29 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

void	ft_error(char *str, char *s1)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ft_putstr_fd(s1, 2);
		}
		else
			ft_putchar_fd(str[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
}

void	ft_check_r(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			ft_error("neobash: $: Permission denied", file);
	}
	else if (file)
	{
		ft_error("g_neobash: $: No such file or directory", file);
	}
}

void	ft_check_w(char *file)
{
	if (!*file || ft_strchr(file, '/'))
		ft_error("g_neobash: $: No such file or directory", file);
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			ft_error("neobash: $: Permission denied", file);
	}
}
