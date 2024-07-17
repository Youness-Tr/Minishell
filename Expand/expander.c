# include "../Header/headers.h"

char	*ft_expand(char *str)
{
	char *res;
	int	i = 0;

	res = ft_strdup("");
	while (str[i])
	{
		printf("here\n");
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

//i have to put last char** that was executed to update that ('_') var.
//when i write that cmd on my shell -> $_ so i have to execute last cmd.