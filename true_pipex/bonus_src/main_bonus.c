/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:00:07 by ajelloul          #+#    #+#             */
/*   Updated: 2025/01/18 15:43:56 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	fail_pipex(char	*content, int status)
{
	ft_putstr_fd(content, 2);
	exit (status);
}

void	error(void)
{
	perror("Error ");
	exit(1);
}

void	write_heredoc_to_pipe(char **av, int *pipe_fds)
{
	char	*line;
	char	*limiter;
	char	*limiter_with_newline;

	limiter = av[2];
	limiter_with_newline = ft_strjoin(limiter, "\n");
	if (!limiter_with_newline)
		exit(1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line || ft_strcmp(line, limiter_with_newline) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fds[1]);
		free(line);
	}
	free(limiter_with_newline);
	dup2(pipe_fds[1], 1);
	close(pipe_fds[1]);
	exit(0);
}

void	found_here_doc(char	**av)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		status;

	if (pipe(pipe_fds) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (!pid)
	{
		close(pipe_fds[0]);
		write_heredoc_to_pipe(av, pipe_fds);
	}
	else
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
		close(pipe_fds[0]);
		waitpid(pid, &status, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		fail_pipex("./pipex infile cmd1 cmd2 ... cmdn outfile\n", 1);
	pipex = fill_record_to_data(ac, av, env);
	if (ft_strcmp(pipex.av[1], "here_doc") == 0)
	{
		if (ac < 6)
			fail_pipex("./pipex here_doc LIMITER cmd cmd1 file\n", 1);
		pipex.herdoc_flag = -1;
		pipex.counter = 3;
		pipex.fd_outfile = open_file(pipex.av[pipex.ac - 1], file_append);
		found_here_doc(pipex.av);
	}
	else
	{
		pipex.counter = 2;
		pipex.fd_infile = open_file(pipex.av[1], file_read);
		pipex.fd_outfile = open_file(pipex.av[pipex.ac - 1], file_write);
	}
	process_pipeline(pipex);
	close(pipex.fd_infile);
	close(pipex.fd_outfile);
	return (0);
}
