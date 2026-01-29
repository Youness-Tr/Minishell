/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_io_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:16:43 by ajabri            #+#    #+#             */
/*   Updated: 2024/08/15 11:21:51 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

int	ft_out(t_io *io, int flag)
{
	int	fd;

	if (!io->exp_val || !io->exp_val[0])
	{
		ft_error("neobash: $ : ambiguous redirect", io->value);
		return (1);
	}
	else if (count_args(get_cmdagrs(io->exp_val)) > 1)
	{
		ft_error("neobash: $ : ambiguous redirect", io->value);
		return (1);
	}
	fd = open(io->exp_val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_check_w(io->exp_val);
		return (1);
	}
	if (!flag)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (ft_error("neobash : $ : problem", "dup2"), close(fd), 1);
	}
	close(fd);
	return (0);
}

int	ft_in(t_io *io, int flag)
{
	int	fd;

	if (!io->exp_val || !io->exp_val[0])
	{
		ft_error("neobash: $ : ambiguous redirect", io->value);
		return (1);
	}
	else if (count_args(get_cmdagrs(io->exp_val)) > 1)
	{
		ft_error("neobash: $ : ambiguous redirect", io->value);
		return (1);
	}
	fd = open(io->exp_val, O_RDONLY);
	if (fd == -1)
	{
		ft_check_r(io->exp_val);
		return (1);
	}
	if (!flag)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (ft_error("neobash : $ : problem", "dup2"), close(fd), 1);
	}
	close(fd);
	return (0);
}

int	ft_app(t_io *io, int flag)
{
	int	fd;

	if (!io->exp_val || !io->exp_val[0])
	{
		ft_error("neobash: $ : ambiguous redirect", io->value);
		return (1);
	}
	else if (count_args(get_cmdagrs(io->exp_val)) > 1)
	{
		ft_error("neobash: $ : ambiguous redirect", io->value);
		return (1);
	}
	fd = open(io->exp_val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_check_w(io->exp_val);
		return (1);
	}
	if (!flag)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (ft_error("neobash : $ : problem", "dup2"), close(fd), 1);
	}
	close(fd);
	return (0);
}
