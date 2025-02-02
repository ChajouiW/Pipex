/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:34:13 by mochajou          #+#    #+#             */
/*   Updated: 2025/02/01 20:06:30 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_all a, char *arg, int fd, pid_t *pid)
{
	char	**cmd;

	*pid = fork();
	if (*pid == 0)
	{
		cmd = cmd_path(arg, a);
		if (!cmd || !*cmd || a.fdin < 0)
			ft_error(arg, a, cmd, 0);
		(dup2(a.fdout, 1), dup2(a.fdin, 0), close(a.fdout));
		close(a.fdin);
		if (fd >= 0)
			close(fd);
		execve(cmd[0], cmd, a.envp);
		(ft_free(cmd, 0), ft_free(a.s_path, 0));
		exit(errno);
	}
	if (*pid == -1)
		(perror("pipe"), exit(errno));
	else
	{
		close(a.fdout);
		if (a.fdin >= 0)
			close(a.fdin);
	}
}

void	pipex(t_all a, char **av, int *status)
{
	int		t[2];
	int		i;
	pid_t	pid;

	(1) && (i = 2, a.fdin = check_files(av[1], 0, a.b));
	while (i < a.ac - 2)
	{
		pipe(t);
		a.fdout = t[1];
		execute(a, av[i], t[0], &pid);
		a.fdin = t[0];
		i++;
	}
	a.fdout = check_files(av[a.ac - 1], 1, a.b);
	if (a.fdout < 0)
	{
		close(a.fdin);
		ft_error(av[a.ac - 1], a, NULL, -1);
	}
	execute(a, av[i], -1, &pid);
	waitpid(pid, status, 0);
	while (wait(NULL) > 0)
		;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]) && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	usage(int part)
{
	if (part == 1)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
	if (part == 2)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
		exit(1);
	}
	else
	{
		ft_printf("Usage: ./pipex here_doc LIMITER cmd cmd1 file\n");
		exit(1);
	}
}
