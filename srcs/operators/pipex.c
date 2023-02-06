/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:08:36 by loadjou           #+#    #+#             */
/*   Updated: 2023/02/02 11:40:41 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_cmd_path(char **env, t_token *tok)
{
	int		i;
	char	*cmd;
	char	*cmd_path;

	i = 0;
	cmd = ft_strjoin("/", tok->cmd[0]);
	while (env[i++])
	{
		cmd_path = ft_strjoin(env[i], cmd);
		if (env[i] && access(cmd_path, (F_OK, X_OK)) == 0)
		{
			free(cmd);
            tok->cmd_path = cmd_path;
            free(cmd_path);
            return ;
		}
		free(cmd_path);
	}
	free(cmd);
	free(cmd_path);
    	error_msg("Command not found! Please try again...", 2);
}


bool	run_process(t_token *tok)
{
	char	*cmd;
	if (pipe(tok->pfd) == -1)
		error_msg("Pipe creation failed!\n", 2);
	tok->child = fork();
	if (tok->child == -1)
		error_msg("Fork creation failed!\n", 2);
	if (tok->child == 0)
	{
		close(tok->pfd[0]);
		dup2(tok->pfd[1], STDOUT_FILENO);
		dup2(tok->infile, STDIN_FILENO);
        get_cmd_path(tok->table->envp, tok);
		if (execve(tok->cmd_path, tok->cmd, tok->table->envp) == -1)
			error_msg("Command execution failed}!\n", 2);
	}
	else
	{
		close(tok->pfd[1]);
		dup2(tok->pfd[0], STDIN_FILENO);
		waitpid(tok->child, NULL, WNOHANG);
		ft_free_array(tok->cmd);
		free(cmd);
	}
	return (true);
}

void	pipex_bonus(t_token *tok, int i)
{
	char	*cmd;
	char	**opt;

	while (i < tok->table->tk_num)
		run_process(&tok[i++]);
	dup2(tok->infile, STDOUT_FILENO);
	if (execve(tok->cmd_path, tok->cmd, tok->table->envp) == -1)
		error_msg("Command execution failed!\n", 2);
}