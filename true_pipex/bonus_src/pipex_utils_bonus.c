/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:00:02 by ajelloul          #+#    #+#             */
/*   Updated: 2025/01/15 11:27:50 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	**find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			return (ft_split(ft_strchr(env[i], '/'), ':'));
		}
		i++;
	}
	return (NULL);
}

t_pipex	fill_record_to_data(int ac, char **av, char **env)
{
	t_pipex	args;

	args.ac = ac;
	args.av = av;
	args.env = env;
	return (args);
}

int	open_file(char *pathname, t_file_mode mode)
{
	int	fd;

	if (mode == file_write)
		fd = open (pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (mode == file_read)
		fd = open (pathname, O_RDONLY);
	if (mode == file_append)
		fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(pathname);
		exit (1);
	}
	return (fd);
}

void	free_2d(char **list)
{
	int	u;

	u = 0;
	while (list[u])
	{
		free (list[u++]);
	}
	free (list);
}

char	*find_path_of_command(t_pipex pipex, char *man_cmd)
{
	char	*join_slash;
	char	*join_command;
	char	**path;
	int		x;

	x = 0;
	path = find_path(pipex.env);
	if (!path)
		fail_pipex("Error: Path not found.\n", 1);
	while (path[x])
	{
		join_slash = ft_strjoin(path[x], "/");
		join_command = ft_strjoin(join_slash, man_cmd);
		free (join_slash);
		if (access(join_command, F_OK | X_OK) == 0)
		{
			free_2d(path);
			return (join_command);
		}
		free (join_command);
		x++;
	}
	free_2d(path);
	return (man_cmd);
}
