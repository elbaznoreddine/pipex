/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:50:44 by noel-baz          #+#    #+#             */
/*   Updated: 2025/01/25 08:23:40 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		exit(1);
	path = get_path(s_cmd[0], env);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_free_tab(s_cmd);
		free(path);
		exit(1);
	}
}

void	first_child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	close(p_fd[1]);
	close(fd);
	exec(av[2], env);
}

void	second_child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	dup2(p_fd[0], 0);
	dup2(fd, 1);
	close(p_fd[0]);
	close(p_fd[1]);
	close(fd);
	exec(av[3], env);
}

static void	fork_processes(char **av, char **env, int *p_fd)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		first_child(av, p_fd, env);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
		second_child(av, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	int	p_fd[2];

	if (ac == 5 && *env)
	{
		if (pipe(p_fd) == -1)
			exit(1);
		fork_processes(av, env, p_fd);
	}
	else
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		return (1);
	}
	return (0);
}
