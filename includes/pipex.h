/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:52:26 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/07 21:05:51 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "get_next_line.h"
# include "../libft/libft.h"

# define PIPE_ERROR "\033[31mError. Failed to create a pipe.\033[0m"
# define FIL1_ERROR "\033[31mError. The file does not exist.\033[0m"
# define FIL2_ERROR "\033[31mError. Could not open second file.\033[0m"
# define CMDS_ERROR "\033[31mError. The entered command is invalid.\033[0m"
# define FORK_ERROR "\033[31mError. Failed to create a new proccess.\033[0m"
# define ARGS_ERROR "\033[31mError. The number of arguments is invalid.\033[0m"

extern char	**environ;

typedef struct s_fifo
{
	int		curr;
	int		fd[2];
	int		end[2][2];
	char	*here_doc;
	char	**command_list;
	int		total_commands;
}	t_fifo;

void	ft_get_path(char **envp, char **command);
t_fifo	*ft_fifo_init(int argc, char **argv);
void	ft_exec_command(char *full_command);
void	ft_clear_array(char **array);

#endif