/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:40:01 by gehebert          #+#    #+#             */
/*   Updated: 2023/03/23 14:53:20 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_status;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

char	*ms_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**ms_setenv(char *var, char *value, char **envp, int n)
{
	char	*aux[2];
	int		i[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);
		}
	}
	envp = ft_mx_ext(envp, aux[1]);
	free(aux[1]);
	return (envp);
}

static int	var_envp(char *argv, char **envp, int k[2])
{
	int	pos;

	k[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[k[1]])
	{
		printf("____k[1]= %d \n", k[1]);
		if (!ft_strncmp(envp[k[1]], argv, pos + 1))
			return (1);
		k[1]++;
	}
	return (0);
}

int	ms_unset(t_table *tab)
{
	char	**argv;
	char	*aux;
	int		k[2];

	k[0] = 0;
	argv = ((t_node *)tab->cmdl->content)->cmd;
	if (ft_mx_len(argv) >= 2)
	{
		while (argv[++k[0]])
		{
			if (argv[k[0]][ft_strlen(argv[k[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[k[0]], "=");
				free(argv[k[0]]);
				argv[k[0]] = aux;
			}
			if (var_envp(argv[k[0]], tab->envp, k))
			{
				printf("goto [:%d] k[1]= %d \n", ft_mx_len(tab->envp), k[1]);
				ft_mx_rpl(&tab->envp, NULL, k[1]);
				printf("rtrn [:%d]  \n", ft_mx_len(tab->envp));
			}
		}
	}
	return (0);
}
