/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:31:07 by ajelloul          #+#    #+#             */
/*   Updated: 2025/01/16 10:21:17 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fail_pipex(char	*content, int status)
{
	ft_putstr_fd(content, 2);
	exit (status);
}

int	main(int ac, char	**av, char	**env)
{
	t_pipex	pipex;
	int		status;

	if (ac != 5)
		fail_pipex("./pipex infile cmd cmd outfile\n", 1);
	pipex = fill_record_to_data(ac, av, env);
	if (pipe(pipex.pipe_fds) == -1)
		exit(1);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		exit(1);
	if (pipex.pid1 == 0)
		child_process1(pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		exit(1);
	if (!pipex.pid2)
		child_process2(pipex);
	close (pipex.pipe_fds[0]);
	close (pipex.pipe_fds[1]);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	close(pipex.fd_infile);
	close(pipex.fd_outfile);
	return (0);
}
