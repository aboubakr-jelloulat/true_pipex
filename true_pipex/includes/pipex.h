/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:48:01 by ajelloul          #+#    #+#             */
/*   Updated: 2025/01/14 10:56:58 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_pipex
{
	char	**av;
	char	**env;
	char	**path;
	int		fd_infile;
	int		fd_outfile;
	int		pipe_fds[2];
	int		ac;
	pid_t	pid1;
	pid_t	pid2;

}	t_pipex;

typedef enum e_file_mode
{
	file_write,
	file_read
}	t_file_mode;

t_pipex	fill_record_to_data(int ac, char **av, char **env);
char	**find_path(char **env);
int		open_file(char *pathname, t_file_mode mode);
void	child_process1(t_pipex	pipex);
void	child_process2(t_pipex	pipex);
char	*find_path_of_command(t_pipex pipex, char *man_cmd);
void	free_2d(char **list);
void	fail_pipex(char	*content, int status);

#endif