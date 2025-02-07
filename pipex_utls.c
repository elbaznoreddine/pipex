/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:54:47 by noel-baz          #+#    #+#             */
/*   Updated: 2025/01/25 08:29:31 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
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

int	open_file(char *file, int type)
{
	int	fd;

	if (type == 0)
		fd = open(file, O_RDONLY);
	if (type == 1)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	return (fd);
}
