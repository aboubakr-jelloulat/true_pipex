/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:19:47 by ajelloul          #+#    #+#             */
/*   Updated: 2025/01/18 13:16:01 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_pipex	fill_record_to_data(int ac, char **av, char **env)
{
	t_pipex	args;

	args.ac = ac;
	args.av = av;
	args.env = env;
	args.fd_infile = open_file(av[1], file_read);
	args.fd_outfile = open_file(av[4], file_write);
	return (args);
}

void	execution(t_pipex pipex, char	*command)
{
	char	**s_command;
	char	*path_cmd;

	s_command = ft_split(command, ' ');
	path_cmd = find_path_of_command(pipex, s_command[0]);
	if (execve(path_cmd, s_command, pipex.env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_command[0], 2);
		free_2d(s_command);
		exit(1);
	}
}

void	child_process2(t_pipex	pipex)
{
	dup2 (pipex.fd_outfile, 1);
	dup2(pipex.pipe_fds[0], 0);
	close (pipex.pipe_fds[1]);
	close(pipex.pipe_fds[0]);
	close(pipex.fd_outfile);
	execution(pipex, pipex.av[3]);
}

void	child_process1(t_pipex	pipex)
{
	dup2 (pipex.fd_infile, 0);
	dup2(pipex.pipe_fds[1], 1);
	close (pipex.pipe_fds[0]);
	close(pipex.pipe_fds[1]);
	close(pipex.fd_infile);
	execution(pipex, pipex.av[2]);
}
