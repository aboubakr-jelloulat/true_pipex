/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:03:48 by ajelloul          #+#    #+#             */
/*   Updated: 2025/01/18 13:19:02 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4

# endif

typedef struct s_pipex
{
	char	**av;
	char	**env;
	int		fd_infile;
	int		fd_outfile;
	int		ac;
	int		counter;
	int		pipe_fds[2];
	int		herdoc_flag;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

typedef enum e_file_mode
{
	file_write,
	file_read,
	file_append
}	t_file_mode;

t_pipex	fill_record_to_data(int ac, char **av, char **env);
void	fail_pipex(char	*content, int status);
int		open_file(char *pathname, t_file_mode mode);
char	*get_next_line(int fd);
char	*find_path_of_command(t_pipex pipex, char *man_cmd);
void	process_pipeline(t_pipex pipex);
void	free_2d(char **list);
void	error(void);

#endif