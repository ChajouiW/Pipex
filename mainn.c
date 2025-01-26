/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:11:28 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/26 14:57:08 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_all
{
	t_io	fd;
	char	**envp;
	int		ac;

}	t_all;

t_all	g_all;

void	ft_freee(char **s)
{
	int i = 0;
	if (!s || !*s)
		return;
	while(s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

/*int main(int ac, char **av, char **env)
{
	char	*path = env_path(env);
	char	**s_path = ft_split(path, ':');
	char	**s = cmd_path(av[1], s_path);
	for(int i = 0; s[i]; i++)
	{
		printf("%s\n", s[i]);
		free(s[i]);
	}
	ft_free(s_path);
	free(s);
}
*/
void	execute(char *cmd_arg, char **path, int next_in)
{
	int	pid;
	char	**cmd;

	pid = fork();
	cmd = cmd_path(cmd_arg, path);
	if (pid == 0)
	{
		dup2(g_all.fd.in, 0);
		close(g_all.fd.in);
		dup2(g_all.fd.out, 1);
		close(next_in);
		if (!cmd)
		{
			ft_freee(path);
			exit(1);
		}
		execve(cmd[0], cmd, NULL);
		ft_freee(cmd);
	}
	else
	{
		close(g_all.fd.in);
		close(g_all.fd.out);
		if (!cmd)
			ft_printf("command not found: %s\n", cmd_arg);
		ft_freee(cmd);
	}
//	??????????? ach tari ???????????
}

void	pipex(int ac, char **av, char	**path)
{
//	char	**cmd_path; // tabhdil
	int	fds[2];
//	t_io	fd;
	int	i;

	i = 2;
	g_all.fd.in = check_files(av[1], 0);
	if (g_all.fd.in < 0)
		g_all.fd.in = open("/dev/null", O_RDONLY);
	while(i < ac - 2)
	{
		pipe(fds);
		g_all.fd.out = fds[1];
		execute(av[i], path, fds[0]);
		g_all.fd.in = fds[0];
		i++;
	}
	g_all.fd.out = check_files(av[ac - 1], 1);
	if (g_all.fd.out < 0)
	{
		printf("permission denied: %s\n", av[ac - 1]);
		ft_freee(path);
		exit(1);
	}
	execute(av[ac - 2], path, fds[0]);
	while(wait(NULL) > 0)
		;
}

int	main(int ac, char **av, char **env)
{
	char	*path;
	char	**s_path;

	if (ac != 5)
		exit(1);
	g_all.envp = env;
	g_all.ac = ac;
	path = env_path(env);
	s_path = ft_split(path, ':');
	pipex(ac, av, s_path);
	ft_freee(s_path);
	return (3);
}
