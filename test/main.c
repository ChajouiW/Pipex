/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:05:05 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/24 16:26:21 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

typedef struct s
{
	int	in_fd;
	int	out_fd;
}	t_data;

/*char	*check_valid(char **env)
{
	char	*path;
	int	i;

	i = 0;
	while(env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_strnstr(env[i], "PATH=", 5);
			break;
		}
		i++;
	}
	return (path + 5);
}*/

void	execute(t_data fds, char *cmd, char **env, int next_in)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fds.in_fd, 0);
		close(fds.in_fd);
		dup2(fds.out_fd, 1);

		close(next_in);
//		check_valid();
	/*------function----*/
		char *path;
		path = 0;
		char	**args = ft_split(cmd, ' ');
		path = ft_strjoin("/usr/bin", args[0]);
		execve(path, args, env);
	}
	else
	{
		close(fds.in_fd);
		close(fds.out_fd);
	}
	
}

/*int	ft_error(char *s, int fd)
{
	if (fd == 0)
	{
		if (access(s, F_OK) == -1)
			printf("no such file or directory: %s", s);
		else if (access(s, R_OK) == -1)
			printf("permission denied: %s", s);
		return (1);
	}
	else
		fd = open(s, O_WRONLY, 0644);
	return (fd);
}*/
int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		i;
	int		t[2];

	if (ac < 5)
		return (0);
	data.in_fd = open(av[1], O_RDONLY);
	i = 2;
	while (av[i + 2] != NULL)
	{
//		if (i == 2 && data.in_fd < 0)
//			(1) && (i += ft_error(av[1], 0), continue);
		pipe(t);
		data.out_fd = t[1];
		execute(data, av[i], env, t[0]);
		data.in_fd = t[0];
		i++;
	}
	data.out_fd = open(av[ac - 1], O_WRONLY);
//	if (data.out_fd < 0)
//		data.out_fd = ft_error(av[ac - 1], 1);
	execute(data, av[i], env, t[0]);
	while (wait(NULL) > 0)
		;
	return (0);
}
