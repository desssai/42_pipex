/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:51:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/08 17:56:32 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_read_from_stdin(t_fifo *fifo)
{
	char	*line;

	close(fifo->end[fifo->curr][0]);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, fifo->here_doc, ft_strlen(fifo->here_doc))
			&& line[ft_strlen(fifo->here_doc)] == '\n')
		{
			free(line);
			break ;
		}
		else
			ft_putstr_fd(line, fifo->end[fifo->curr][1]);
		if (line)
			free(line);
		line = NULL;
		line = get_next_line(0);
	}
	close(STDIN_FILENO);
	exit(EXIT_SUCCESS);
}

static void	ft_pipe_and_fork(t_fifo *fifo, int i, int *id)
{
	if (fifo && pipe(fifo->end[fifo->curr]) == -1)
	{
		ft_putendl_fd(PIPE_ERROR, 2);
		exit(EXIT_FAILURE);
	}
	if (id)
	{
		if (!i || *id)
			*id = fork();
		if (*id == -1)
		{
			ft_putendl_fd(FORK_ERROR, 2);
			exit(EXIT_FAILURE);
		}
	}
}

static void	ft_pipe_switch_exec(t_fifo *fifo, int i)
{
	if (!i && !fifo->here_doc)
		dup2(fifo->fd[0], STDIN_FILENO);
	if (!i && fifo->here_doc)
		ft_read_from_stdin(fifo);
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
	ft_exec_command(fifo->command_list[i]);
}

static void	ft_pipex(t_fifo *fifo)
{
	int		i;
	pid_t	id;

	i = -1;
	id = 0;
	while (fifo->command_list[++i])
	{
		ft_pipe_and_fork(fifo, i, &id);
		if (!id)
			ft_pipe_switch_exec(fifo, i);
		close(fifo->end[1 - fifo->curr][0]);
		close(fifo->end[fifo->curr][1]);
		if (fifo->here_doc && !i && id)
			waitpid(id, 0, 0);
		fifo->curr = 1 - fifo->curr;
	}
	close(fifo->end[1 - fifo->curr][0]);
	close(fifo->fd[0]);
	close(fifo->fd[1]);
	if (fifo->here_doc)
		i--;
	while (i-- > 0)
		wait(NULL);
	free(fifo);
}

int	main(int argc, char **argv)
{
	t_fifo	*fifo;

	if (argc < 5)
		ft_putendl_fd(ARGS_ERROR, 2);
	else
	{
		fifo = ft_fifo_init(argc, argv);
		if (fifo)
			ft_pipex(fifo);
	}
	return (0);
}
