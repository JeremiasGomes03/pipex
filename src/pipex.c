/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerda-si <jerda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:02:25 by jerda-si          #+#    #+#             */
/*   Updated: 2024/12/12 21:06:02 by jerda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(char *argv, char **envp)
{
	int		i;
	char	*path;
	char	**cmd;

	i = -1;
	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
	{
		free_cmd(cmd);
		ft_putstr_fd("pipex: invalid command\n", 2);
		exit(EXIT_FAILURE);
	}
	path = search_for_path(cmd[0], envp);
	if (!path)
	{
		valid_path(cmd);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("pipex: failed execve");
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
}

void	sub_process(char **argv, char **envp, int *fd)
{
	int	file_in;

	file_in = open(argv[1], O_RDONLY, 0644);
	if (file_in == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error duplicating fd[1] for STDOUT");
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	if (dup2(file_in, STDIN_FILENO) == -1)
	{
		perror("Error duplicating file_in for STDIN");
		exit(EXIT_FAILURE);
	}
	close(file_in);
	close(fd[0]);
	ft_exec(argv[2], envp);
}

void	main_process(char **argv, char **envp, int *fd)
{
	int	file_out;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("Error duplicating fd[0] for STDIN");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	if (dup2(file_out, STDOUT_FILENO) == -1)
	{
		perror("Error duplicating file_out for STDOUT");
		exit(EXIT_FAILURE);
	}
	close(file_out);
	close(fd[1]);
	ft_exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit (1);
	}
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		sub_process(argv, envp, fd);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		main_process(argv, envp, fd);
	}
}
