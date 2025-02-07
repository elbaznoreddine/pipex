/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:02:53 by noel-baz          #+#    #+#             */
/*   Updated: 2025/01/25 01:31:04 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define MSG_ERROR "./pipex here_doc LIMITER cmd1 cmd2 cmd3 ... cmdn outfile\n"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

void	middle_child(char *cmd, int *prev_pipe, int *next_pipe, char **env);
void	ft_free_tab(char **tab);
void	here_doc(char *limiter, int *fd);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
int		open_file(char *file, int type);
void	exec(char *cmd, char **env);
void	first_child(char **av, int *first_pipe, char **env);
void	last_child(char **av, int *prev_pipe, char **env, int ac);

#endif