/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:02:13 by noel-baz          #+#    #+#             */
/*   Updated: 2025/01/25 08:28:49 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static int	get_env_key_length(char *str)
{
	int	length;

	length = 0;
	while (str[length] && str[length] != '=')
		length++;
	return (length);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		key_len;
	char	*sub;

	if (!name || !env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		key_len = get_env_key_length(env[i]);
		sub = ft_substr(env[i], 0, key_len);
		if (!sub)
			return (NULL);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + key_len + 1);
		}
		free(sub);
		i++;
	}
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
		exit(1);
	}
}
