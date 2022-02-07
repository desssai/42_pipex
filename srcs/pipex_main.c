/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/06 23:58:00 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec_command(char *full_command)
{
	char const	*command[] = {"pipex", "-c", NULL, NULL};

	ft_get_path(environ, &full_command);
	command[2] = full_command;
	execve("/bin/bash", (char *const *)command, environ);
	exit(EXIT_FAILURE);
}

void	ft_pipe_switch(t_fifo *fifo, int i)
{
	if (!i)
		dup2(fifo->fd[0], STDIN_FILENO);
	if (i > 0)
	{
		dup2(fifo->end[1 - fifo->curr][0], STDIN_FILENO);
		close(fifo->end[1 - fifo->curr][0]);
	}
	if (i < fifo->total_commands - 1)
	{
		dup2(fifo->end[fifo->curr][1], STDOUT_FILENO);
		close(fifo->end[fifo->curr][0]);
		close(fifo->end[fifo->curr][1]);
	}
	if (i == fifo->total_commands - 1)
		dup2(fifo->fd[1], STDOUT_FILENO);
	close(fifo->fd[0]);
	close(fifo->fd[1]);
}

void	ft_pipex(t_fifo *fifo)
{
	int		i;
	pid_t	id;

	i = -1;
	id = 0;
	while (fifo->command_list[++i])
	{
		if (pipe(fifo->end[fifo->curr]) == -1)
			exit(2);
		id = fork();
		if (id == -1)
			exit(3);
		if (!id)
		{
			ft_pipe_switch(fifo, i);
			ft_exec_command(fifo->command_list[i]);
		}
		close(fifo->end[1 - fifo->curr][0]);
		close(fifo->end[fifo->curr][1]);
		fifo->curr = 1 - fifo->curr;
	}
	close(fifo->end[1 - fifo->curr][0]);
	close(fifo->fd[0]);
	close(fifo->fd[1]);
	while (i--)
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
			ft_pipex(fifo);
	}
	return (0);
}
