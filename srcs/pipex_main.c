/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/05 23:52:33 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	g_curr;

void	ft_exec_command(char *full_command)
{
	char	**command_flags;
	char	*command_exec;
	char	**path;
	int		i;

	i = -1;
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
	exit(EXIT_FAILURE);
}

void	ft_cringe_code(t_fifo *fifo, char *command, int i, int total_commands)
{
	if (!i)
	{
		dup2(fifo->fd[0], STDIN_FILENO);
		close(fifo->fd[0]);
	}
	if (i > 0)
	{
		dup2(fifo->end[1 - g_curr][0], STDIN_FILENO);
		close(fifo->end[1 - g_curr][0]);
	}
	if (i < total_commands - 1)
	{
		dup2(fifo->end[g_curr][1], STDOUT_FILENO);
		close(fifo->end[g_curr][0]);
		close(fifo->end[g_curr][1]);
	}
	if (i == total_commands - 1)
	{
		dup2(fifo->fd[1], STDOUT_FILENO);
		close(fifo->fd[1]);
	}
	ft_exec_command(command);
}

void	ft_pipex(t_fifo *fifo, char **commands, int total_commands)
{
	int		i;
	pid_t	id;

	i = -1;
	id = 0;
	while (commands[++i])
	{
		if (pipe(fifo->end[g_curr]) == -1)
			exit(2);
		id = fork();
		if (id == -1)
			exit(3);
		if (!id)
			ft_cringe_code(fifo, commands[i], i, total_commands);
		close(fifo->end[1 - g_curr][0]);
		close(fifo->end[g_curr][1]);
		g_curr = 1 - g_curr;
	}
	close(fifo->end[1 - g_curr][0]);
	i = -1;
	while (++i < total_commands - 1)
		wait(NULL);
}

int	main(int argc, char **argv)
{
	t_fifo	*fifo;

	if (argc < 5)
		ft_putendl_fd(ARGS_ERROR, 2);
	else
	{
		fifo = ft_files_validation(argv[1], argv[argc - 1]);
		if (fifo)
			ft_pipex(fifo, ft_get_commands(&argv[2], argc - 2), argc - 3);
	}
	return (0);
}
