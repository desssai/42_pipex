/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:31:15 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/07 21:08:18 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_clear_fifo(t_fifo **fifo)
{
	if (!(*fifo)->here_doc && (*fifo)->fd[0] < 0)
		ft_putendl_fd(FIL1_ERROR, 2);
	if ((*fifo)->fd[1] < 0)
		ft_putendl_fd(FIL2_ERROR, 2);
	if (!(*fifo)->here_doc && (*fifo)->fd[0])
		close((*fifo)->fd[0]);
	if ((*fifo)->fd[1] > -1)
		close((*fifo)->fd[1]);
	free(*fifo);
	*fifo = NULL;
	exit(EXIT_FAILURE);
}

static void	ft_get_command_list(t_fifo *fifo, char **commands)
{
	fifo->command_list = &commands[2];
	fifo->command_list[fifo->total_commands] = NULL;
}

t_fifo	*ft_fifo_init(int argc, char **argv)
{
	t_fifo	*fifo;

	fifo = (t_fifo *)malloc(sizeof(t_fifo));
	if (!fifo)
		return (NULL);
	fifo->fd[0] = open(argv[1], O_RDONLY);
	fifo->total_commands = argc - 3;
	fifo->here_doc = NULL;
	fifo->end[0][0] = -1;
	fifo->end[0][1] = -1;
	fifo->end[1][0] = -1;
	fifo->end[1][1] = -1;
	fifo->curr = 0;
	if (!ft_strncmp("here_doc", argv[1], 9))
		fifo->here_doc = argv[2];
	if (!fifo->here_doc && fifo->fd[0] < 0)
		ft_clear_fifo(&fifo);
	if (!fifo->here_doc)
		fifo->fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fifo->fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fifo->fd[1] < 0)
		ft_clear_fifo(&fifo);
	ft_get_command_list(fifo, argv);
	return (fifo);
}

static void	ft_get_path_command(char **envp, char **command)
{
	char	*path;
	char	*temp;

	path = NULL;
	while (*envp)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
		{
			path = (*envp + 5);
			break ;
		}
		envp++;
	}
	if (!path)
		*command = ft_strjoin("unset PATH;", *command, 0, 0);
	else
	{
		temp = ft_strjoin("export PATH=", path, 0, 0);
		temp = ft_strjoin(temp, ";", 1, 0);
		*command = ft_strjoin(temp, *command, 1, 0);
	}
}

void	ft_exec_command(char *full_command)
{
	char const	*command[] = {"pipex", "-c", NULL, NULL};

	ft_get_path_command(environ, &full_command);
	command[2] = full_command;
	execve("/bin/bash", (char *const *)command, environ);
	exit(EXIT_FAILURE);
}
