/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:12:07 by bylkus            #+#    #+#             */
/*   Updated: 2023/03/07 14:20:31 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strcmp_c(char *s1, char *s2, char until)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != until)
		i++;
	return (s1[i] - s2[i]);
}

static int	ft_strlen_c(char *str, char until)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != until)
		i++;
	return (i);
}

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

char	**edit_env(char **envp, int pos)
{
	if(!envp)
		return NULL;
	while (envp && envp[pos + 1])
	{
		envp[pos] = envp[pos + 1];
		pos++;
	}
	envp[pos] = NULL;
	return (envp);
}
 
static char *cmd_to_unset(char *envp)
{
	char *cmd;

	cmd = ft_substr(envp, 0, ft_strlen_c(envp, '='));
	if(!cmd || !envp)
		return NULL;
	return cmd;
}
 
int	unset(char **cmd, char **envp)
{
	int	i;
	char *cmd_trim;
	i = 0;
	if (!cmd[1] || cmd[2])
	{
		printf("Missmatch args nb\n");
		return (0);
	}
	while (envp[i])
	{
		cmd_trim = cmd_to_unset(envp[i]);
		if (ft_strcmp(cmd_trim, cmd[1]) == 0)
		{
			free(cmd_trim);
			envp = edit_env(envp, i);
			return (1);
		}
		free(cmd_trim);
		i++;
	}
	return (0);
}


static int	check_export_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while(str[i] != '=')
		{
			if(!ft_isalpha(str[i]) && str[i] != '_')
				return 0;
			i++;
		}
		if (i > 0 && str[i] == '=' && str[i + 1] != '=' && str[i - 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

static int	is_already_var(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen_c(envp[i], '=')) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**new_envp(char **envp, char *var)
{
	int		i;
	int		pos;
	int		len;
	char	**new_envp;

	len = ft_arraylen(envp) + 2;
	new_envp = ft_calloc(sizeof(char *), len);
	if (!new_envp)
		return (NULL);
	new_envp[0] = ft_strdup(var);
	i = 1;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		// printf("%s\n", new_envp[i]);
		i++;
	}
	printf("********************* tab lenght: %d\n", ft_mx_len(new_envp));
	// ft_free_array(envp);
	return (new_envp);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

int	ms_export(char **cmd, char **envp)
{
	int	pos;
	
	if (cmd[1] && check_export_cmd(cmd[1]))
	{
		pos = is_already_var(envp, cmd[1]);
		if (pos > -1)
		{
			envp[pos] = ft_strdup(cmd[1]);
			printf("entered string: %s\n", envp[pos]);
		}
		else
			envp = new_envp(envp, cmd[1]);
		if (!envp)
			return (0);
	}
	else if (!cmd[1])
		print_tab(envp);
	else
	{
		printf("Bad var format\n");
		return (0);
	}
	return (1);
}
