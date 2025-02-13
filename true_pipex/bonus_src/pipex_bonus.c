/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:59:57 by ajelloul          #+#    #+#             */
/*   Updated: 2025/01/18 13:34:45 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	execution(t_pipex pipex, char *command)
{
	char	**s_command;
	char	*path_cmd;

	s_command = ft_split(command, ' ');
	path_cmd = find_path_of_command(pipex, s_command[0]);
	if (execve(path_cmd, s_command, pipex.env))
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_command[0], 2);
		free_2d(s_command);
		exit(1);
	}
}

void	child(t_pipex pipex, char *cmd, int prev_fd, int last_cmd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	else if (prev_fd == -1 && pipex.herdoc_flag != -1)
	{
		dup2(pipex.fd_infile, 0);
		close(pipex.fd_infile);
	}
	if (!last_cmd)
	{
		dup2(pipex.pipe_fds[1], 1);
		close(pipex.pipe_fds[1]);
		close(pipex.pipe_fds[0]);
	}
	else
	{
		dup2(pipex.fd_outfile, 1);
		close(pipex.fd_outfile);
	}
	execution(pipex, cmd);
}

void	parent_process(t_pipex pipex, int *prev_fd)
{
	close(pipex.pipe_fds[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = pipex.pipe_fds[0];
}

t_pipex	create_new_process(t_pipex pipex, int *prev_fd)
{
	pid_t	pid;
	int		last_cmd;

	last_cmd = (pipex.counter == pipex.ac - 2);
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child(pipex, pipex.av[pipex.counter], *prev_fd, last_cmd);
	else
	{
		if (!last_cmd)
			parent_process(pipex, prev_fd);
		pipex.counter++;
	}
	return (pipex);
}

void	process_pipeline(t_pipex pipex)
{
	int	prev_fd;

	prev_fd = -1;
	while (pipex.counter < pipex.ac - 1) 
	{
		if (pipex.counter < pipex.ac - 2 && pipe(pipex.pipe_fds) == -1)
			error();
		pipex = create_new_process(pipex, &prev_fd);
	}
	if (prev_fd != -1)
	{
		close(prev_fd);
	}
	while (wait(NULL) != -1)
		;
}
