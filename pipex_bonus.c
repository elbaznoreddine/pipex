/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 04:08:09 by noel-baz          #+#    #+#             */
/*   Updated: 2025/02/07 22:44:40 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(char **av, int *first_pipe, char **env)
{
	int	fd;

	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		here_doc(av[2], first_pipe);
		close(first_pipe[1]);
		close(first_pipe[0]);
		exit(0);
	}
	else
	{
		fd = open_file(av[1], 0);
		dup2(fd, 0);
		dup2(first_pipe[1], 1);
		close(first_pipe[0]);
		close(first_pipe[1]);
		close(fd);
		exec(av[2], env);
	}
}

void	last_child(char **av, int *prev_pipe, char **env, int ac)
{
	int	fd;

	fd = open_file(av[ac - 1], 1);
	dup2(prev_pipe[0], 0);
	dup2(fd, 1);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	close(fd);
	exec(av[ac - 2], env);
}

void	close_all_pipes(int pipes[2][2], int current)
{
	close(pipes[current][0]);
	close(pipes[current][1]);
}

int	create_middle_and_last_children(int ac, char **av,
	char **env, int pipes[2][2])
{
	int		i;
	int		current;
	pid_t	pid;

	i = 3;
	current = 0;
	while (i < ac - 2)
	{
		if (pipe(pipes[!current]) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			middle_child(av[i], pipes[current], pipes[!current], env);
		close_all_pipes(pipes, current);
		current = !current;
		i++;
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		last_child(av, pipes[current], env, ac);
	return (close_all_pipes(pipes, current), pid);
}

int	main(int ac, char **av, char **env)
{
	int		pipes[2][2];
	pid_t	pid;
	int		status;

	if (ac >= 5 && *env)
	{
		if (pipe(pipes[0]) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			first_child(av, pipes[0], env);
		pid = create_middle_and_last_children(ac, av, env, pipes);
		waitpid(pid, &status, 0);
		while (wait(NULL) > 0)
			;
		return (WEXITSTATUS(status));
	}
	else
	{
		ft_putstr_fd(MSG_ERROR, 2);
		return (1);
	}
}
