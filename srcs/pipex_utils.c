/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:31:15 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/04 20:39:10 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	*ft_files_validation(char *filename1, char *filename2)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 2);
	fd[0] = open(filename1, O_RDONLY);
	fd[1] = open(filename2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[0] < 0)
	{
		ft_putendl_fd(FIL1_ERROR, 2);
		return (NULL);
	}
	if (fd[1] < 0)
	{
		if (fd[0])
			close(fd[0]);
		ft_putendl_fd(FIL2_ERROR, 2);
		return (NULL);
	}
	return (fd);
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
