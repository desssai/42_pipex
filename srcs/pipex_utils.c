/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:31:15 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/05 23:29:13 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_fifo	*ft_files_validation(char *filename1, char *filename2)
{
	t_fifo	*fifo;

	fifo = (t_fifo *)malloc(sizeof(t_fifo));
	if (!fifo)
		return (NULL);
	fifo->fd[0] = open(filename1, O_RDONLY);
	fifo->fd[1] = open(filename2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fifo->fd[0] < 0)
	{
		ft_putendl_fd(FIL1_ERROR, 2);
		return (NULL);
	}
	if (fifo->fd[1] < 0)
	{
		if (fifo->fd[0])
			close(fifo->fd[0]);
		ft_putendl_fd(FIL2_ERROR, 2);
		return (NULL);
	}
	fifo->end[0][0] = -1;
	fifo->end[0][1] = -1;
	fifo->end[1][0] = -1;
	fifo->end[1][1] = -1;
	return (fifo);
}

char	**ft_get_path_variables(char **envp)
{
	char	**env_paths;
	int		i;

	while (envp)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
			break ;
		envp++;
	}
	env_paths = ft_split((*envp + 5), ':');
	i = -1;
	while (env_paths[++i])
		env_paths[i] = ft_strjoin(env_paths[i], "/", 0);
	return (env_paths);
}

void	ft_clear_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (array[i])
			free(array[i]);
	}
	free(array);
	array = NULL;
}

char	**ft_get_commands(char **command_list, int total_commands)
{
	command_list[total_commands - 1] = NULL;
	return (command_list);
}
