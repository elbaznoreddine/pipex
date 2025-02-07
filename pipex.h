/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:49:38 by noel-baz          #+#    #+#             */
/*   Updated: 2025/01/24 23:47:07 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

void	ft_free_tab(char **tab);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
int		open_file(char *file, int type);
void	exec(char *cmd, char **env);
void	first_child(char **av, int *p_fd, char **env);
void	second_child(char **av, int *p_fd, char **env);

#endif