/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:52:26 by ncarob            #+#    #+#             */
/*   Updated: 2022/02/04 19:27:32 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../libft/libft.h"

# define FIL1_ERROR "\033[31mError. The file does not exist.\033[0m"
# define FIL2_ERROR "\033[31mError. Could not open second file.\033[0m"
# define CMDS_ERROR "\033[31mError. The entered command is invalid.\033[0m"
# define FORK_ERROR "\033[31mError. Failed to create a new proccess.\033[0m"
# define ARGS_ERROR "\033[31mError. The number of arguments is invalid.\033[0m"

extern char	**environ;

char	**ft_get_commands(char **command_list, int total_commands);
int		*ft_files_validation(char *filename1, char *filename2);
char	**ft_get_path_variables(char **envp);
void	ft_clear_array(char **array);

#endif