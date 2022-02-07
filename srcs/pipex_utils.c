/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:31:15 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/07 00:14:24 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_fifo	*ft_files_validation(int argc, char **argv)
{
	t_fifo	*fifo;

	fifo = (t_fifo *)malloc(sizeof(t_fifo));
	if (!fifo)
		return (NULL);
	fifo->total_commands = argc - 2;
	fifo->here_doc = NULL;
	fifo->end[0][0] = -1;
	fifo->end[0][1] = -1;
	fifo->end[1][0] = -1;
	fifo->end[1][1] = -1;
	fifo->curr = 0;
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		fifo->here_doc = argv[2];
		fifo->fd[0] = -1;
		fifo->total_commands--;
	}
	else
		fifo->fd[0] = open(argv[1], O_RDONLY);
	fifo->fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((!fifo->here_doc && fifo->fd[0] < 0) || fifo->fd[1] < 0
		|| ft_get_command_list(fifo, argv))
		ft_clear_fifo(fifo);
	return (fifo);
}

void	ft_get_path(char **envp, char **command)
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
		*command = ft_strjoin("unset PATH;", *command, 0);
	else
	{
		temp = ft_strjoin("export PATH=", path, 0);
		temp = ft_strjoin(temp, ";", 1);
		*command = ft_strjoin(temp, *command, 1);
	}
}

int	ft_get_command_list(t_fifo *fifo, char **commands)
{
	if (fifo->here_doc)
		fifo->command_list = &commands[3];
	else
		fifo->command_list = &commands[2];
	fifo->command_list[fifo->total_commands - 1] = NULL;
}
