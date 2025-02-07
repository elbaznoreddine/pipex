/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utls_bonus2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:47:39 by noel-baz          #+#    #+#             */
/*   Updated: 2025/01/25 02:18:12 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle_child(char *cmd, int *prev_pipe, int *next_pipe, char **env)
{
	dup2(prev_pipe[0], 0);
	dup2(next_pipe[1], 1);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	close(next_pipe[0]);
	close(next_pipe[1]);
	exec(cmd, env);
}

static char	*check_command_path(char **allpath, char *cmd)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = -1;
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**allpath;
	char	*result;

	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath || !cmd)
	{
		ft_free_tab(allpath);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	result = check_command_path(allpath, cmd);
	if (result)
		return (result);
	ft_free_tab(allpath);
	return (NULL);
}

static void	write_temp_file(int fd_temp, char *limiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd_temp, line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(char *limiter, int *fd)
{
	int		fd_temp;
	char	*line;

	fd_temp = open("/tmp/temp_heredoc", O_CREAT | O_RDWR, 0644);
	if (fd_temp == -1)
		return ;
	write_temp_file(fd_temp, limiter);
	close(fd_temp);
	fd_temp = open("/tmp/temp_heredoc", O_RDONLY);
	if (fd_temp == -1)
		return ;
	line = get_next_line(fd_temp);
	while (line)
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(fd_temp);
	}
	close(fd_temp);
	unlink("/tmp/temp_heredoc");
}
