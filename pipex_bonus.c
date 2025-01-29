/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:44:06 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/28 23:57:58 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	execute(t_all a, char *arg, int fd, int *pid)
{
	char	**cmd;

	*pid = fork();
	if (*pid == 0)
	{
		cmd = cmd_path(arg, a);
		if (!cmd)
			ft_error(arg, a, cmd, 0);
		dup2(a.fdout, 1);
		dup2(a.fdin, 0);
		ft_close(a.fdout, a.fdin);
		close(fd);
		execve(cmd[0], cmd, a.envp);
		ft_freee(cmd);
		ft_freee(a.s_path);
		exit(-1);
	}
	else
		ft_close(a.fdout, a.fdin);
}

void	pipex(t_all a, char **av, int *status)
{
	int	t[2];
	int	i;
	int	pid;

	i = 2;
	a.fdin = check_files(av[1], 0);
	if (a.fdin < 0)
		a.fdin = open("/dev/null", O_RDONLY);
	while (i < a.ac - 2)
	{
		pipe(t);
		a.fdout = t[1];
		execute(a, av[i], t[0], &pid);
		a.fdin = t[0];
		i++;
	}
	a.fdout = check_files(av[a.ac - 1], 1);
	if (a.fdout < 0)
		ft_error(av[a.ac - 1], a, NULL, -1);
	execute(a, av[i], t[0], &pid);
	waitpid(pid, status, 0);
	while (wait(NULL) > 0)
		;
}

int	main(int ac, char **av, char **env)
{
	t_all	needed;
	int		status;

	status = 0;
	if (ac < 5)
	{
		ft_printf("Invalid argument try: ./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
	needed.ac = ac;
	needed.envp = env;
	needed.s_path = ft_split(env_path(env), ':');
	pipex(needed, av, &status);
	ft_freee(needed.s_path);
	exit(WEXITSTATUS(status));
}
