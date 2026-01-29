/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:41:10 by kali              #+#    #+#             */
/*   Updated: 2024/08/15 15:45:25 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/headers.h"

t_shell	g_neobash;

void	ft_init_g_neobash(char **env)
{
	g_neobash.envp = env;
	get_env_list(env);
	g_neobash.prs_state = 0;
	g_neobash.hdoc = 1;
	g_neobash.in = dup(0);
	g_neobash.out = dup(1);
	g_neobash.here_dc_ex = false;
	g_neobash.paths = grep_paths(env);
	g_neobash.level = ft_atoi(get_env_val("SHLVL"));
	if (g_neobash.level + 1 < 0)
		g_neobash.level = -1;
	else if (g_neobash.level + 1 >= 1000)
	{
		ft_error("bash: warning: shell level ($) too high, resetting to 1",
			ft_itoa(g_neobash.level + 1));
		g_neobash.level = 0;
	}
	update_env("SHLVL", ft_itoa(++g_neobash.level));
	g_neobash.exp_here = true;
}

int	ft_parenthesis(void)
{
	t_token	*tmp;

	tmp = g_neobash.tokens;
	while (tmp)
	{
		if (tmp->type == L_PARENT && !tmp->next)
		{
			ft_error("neobash: syntax error near unexpected token `$'",
				tmp->value);
			g_neobash.status = 2;
			return (0);
		}
		else if (tmp->type == L_PARENT && tmp->next->type == R_PARENT)
		{
			ft_error("neobash: syntax error near unexpected token `$'",
				tmp->next->value);
			g_neobash.status = 2;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_checks(void)
{
	if (g_neobash.line)
		add_history(g_neobash.line);
	if (!ft_coutquotes())
	{
		free(g_neobash.line);
		return (0);
	}
	ft_lexer();
	free(g_neobash.line);
	return (ft_parenthesis());
}

void	neoshell(void)
{
	while (true)
	{
		ft_init_signals();
		g_neobash.line = readline(PROMPT);
		if (g_neobash.line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(g_neobash.status);
		}
		signal(SIGINT, SIG_IGN);
		if (!ft_checks())
			continue ;
		if (!g_neobash.tokens)
			continue ;
		if (!synyax_before())
			continue ;
		g_neobash.tree = ft_parser();
		if (g_neobash.prs_state)
		{
			ft_syntax_after();
			g_neobash.prs_state = 0;
			continue ;
		}
		execution();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_init_g_neobash(env);
	neoshell();
	return (0);
}
