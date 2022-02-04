/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/04 20:48:17 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

void	ft_exec_command(int fd1, int fd2, char *full_command)
{
	char	**command_flags;
	char	*command_exec;
	char	**path;
	int		i;

	i = -1;
	close(fd1);
	close(fd2);
	path = ft_get_path_variables(environ);
	command_flags = ft_split(full_command, ' ');
	while (path[++i])
	{
		command_exec = ft_strjoin(path[i], command_flags[0], 0);
		execve(command_exec, command_flags, environ);
		free(command_exec);
	}
	ft_clear_array(command_flags);
	ft_clear_array(path);
}

void	ft_pipex(int fd1, int fd2, char **commands, int total_commands)
{
	int		i;
	pid_t	*ids;
	int		pip[2];

	i = 0;
	ids = (pid_t *)malloc(sizeof(pid_t) * total_commands);
	if (pipe(pip) == -1)
		return ;
	ids[i] = fork();
	if (ids[i] < 0)
		return ;
	while (*commands && ++i < total_commands)
	{
		if (ids[i])
			ids[i] = fork();
		if (!ids[i])
		{
			if (i == 1)
			{
				dup2(fd1, STDIN_FILENO);
				dup2(pip[0], STDOUT_FILENO);
			}
			else if (i == total_commands - 1)
			{
				dup2(pip[0], STDIN_FILENO);
				dup2(fd2, STDOUT_FILENO);
			}
			else if (i % 2 == 0)
			{
				dup2(pip[0], STDIN_FILENO);
				dup2(pip[1], STDOUT_FILENO);
			}
			else if (i % 2 == 1)
			{
				dup2(pip[1], STDIN_FILENO);
				dup2(pip[0], STDOUT_FILENO);
			}
			printf("%d\n", total_commands);
			printf("I am: %d, %d. My parent is: %d\n", ids[i], getpid(), getppid());
			//ft_exec_command(fd1, fd2, *commands);
			close(fd1);
			close(fd2);
			close(pip[0]);
			close(pip[1]);
		}
		commands++;
	}
	close(fd1);
	close(fd2);
	close(pip[0]);
	close(pip[1]);
	if (ids[0] != 0)
		while (wait(NULL) != -1 || errno != ECHILD)
			;
}

int	main(int argc, char **argv)
{
	int	*fd;

	if (argc < 5)
		ft_putendl_fd(ARGS_ERROR, 2);
	else
	{
		fd = ft_files_validation(argv[1], argv[argc - 1]);
		if (!fd)
			return (1);
		ft_pipex(fd[0], fd[1], ft_get_commands(&argv[2], argc - 3), argc - 3);
	}
	return (0);
}
