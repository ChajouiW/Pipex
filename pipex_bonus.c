/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:44:06 by mochajou          #+#    #+#             */
/*   Updated: 2025/02/01 16:10:00 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*fill_content(char *s)
{
	int		len;
	char	*tmp;
	char	*content;
	char	*save;

	content = NULL;
	len = ft_strlen(s);
	tmp = get_next_line(0);
	while (tmp && !ft_strnstr(tmp, s, len))
	{
		save = content;
		if (!content)
			content = ft_strdup(tmp);
		else
			content = ft_strjoin(content, tmp);
		free(save);
		free(tmp);
		ft_printf("here_doc> ");
		tmp = get_next_line(0);
	}
	free(tmp);
	free(s);
	return (content);
}

void	set_myav(t_all a, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < a.ac - 1)
	{
		if (i == 1)
			a.my_av[i] = ft_strdup("/tmp/tmp_file");
		else
			a.my_av[i] = ft_strdup(av[j]);
		i++;
		j++;
	}
	a.my_av[i] = NULL;
}

void	ft_remove(char *file, t_all a)
{
	pid_t	pid;
	char	*cmd;
	char	**path;

	pid = fork();
	if (pid == 0)
	{
		cmd = "rm -f ";
		cmd = ft_strjoin(cmd, file);
		path = cmd_path(cmd, a);
		execve(path[0], path, a.envp);
		free(cmd);
		ft_free(path, 0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	here_doc(t_all a, char **av, int *status)
{
	char	*file_content;

	if (a.ac < 6)
	{
		ft_free(a.s_path, 0);
		usage(3);
	}
	a.my_av = (char **)malloc(sizeof(char *) * a.ac);
	if (!a.my_av)
		return ;
	set_myav(a, av);
	(1) && (a.ac = a.ac - 1, a.b = 1);
	if (access(a.my_av[1], W_OK) == -1)
		ft_remove(a.my_av[1], a);
	ft_printf("here_doc> ");
	a.fdout = open(a.my_av[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	file_content = fill_content(ft_strjoin(av[2], "\n"));
	if (file_content)
		write(a.fdout, file_content, ft_strlen(file_content));
	(close(a.fdout), free(file_content));
	(pipex(a, a.my_av, status), ft_remove(a.my_av[1], a), ft_free(a.my_av, 0));
}

int	main(int ac, char **av, char **env)
{
	t_all	needed;
	int		status;

	if (ac < 5)
		usage(2);
	needed.b = 0;
	needed.ac = ac;
	needed.envp = env;
	needed.s_path = ft_split_cmd(env_path(env), ':');
	if (!ft_strncmp(av[1], "here_doc", 9))
		here_doc(needed, av, &status);
	else
		pipex(needed, av, &status);
	ft_free(needed.s_path, 0);
	exit(WEXITSTATUS(status));
}
