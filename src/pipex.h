/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerda-si <jerda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:30:12 by jerda-si          #+#    #+#             */
/*   Updated: 2024/12/08 01:27:44 by jerda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../librarie/libft/libft.h"

void	ft_exec(char *argv, char **envp);
void	sub_process(char **argv, char **envp, int *fd);
void	main_process(char **argv, char **envp, int *fd);
char	*search_for_path(char *cmd, char **envp);
void	free_cmd(char **cmd);
void	valid_path(char **cmd);

#endif 