/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:23:29 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/29 00:58:45 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freee(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	check_files(char *file_name, int in_out)
{
	int	fd;

	if (in_out == 0)
	{
		if (access(file_name, F_OK) == -1)
			return (ft_printf("no such file or directory: %s\n", file_name), -1);
		if (access(file_name, R_OK) == -1)
		{
			ft_printf("permission denied: %s\n", file_name);
			return (-1);
		}
		fd = open(file_name, O_RDONLY);
	}
	else
	{
		if (access(file_name, F_OK) == -1)
			fd = open(file_name, O_CREAT | O_WRONLY, 0644);
		else
		{
			if (access(file_name, W_OK) == -1)
				return (ft_printf("permission denied: %s\n", file_name), -1);
			fd = open(file_name, O_WRONLY | O_TRUNC);
		}
	}
	return (fd);
}

char	*env_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_strnstr(env[i], "PATH=", 5);
			break ;
		}
		i++;
	}
	return (path + 5);
}

static char	**path_finder(char *cmd_arg, t_all a, char *cmd_path, char **cmd)
{
	int	i;

	i = 0;
	while (a.s_path[i])
	{
		cmd_path = ft_strjoin(a.s_path[i], cmd[0]);
		if (!access(cmd_path, F_OK))
		{
			if (access(cmd_path, X_OK) == -1)
			{
				free(cmd_path);
				ft_error(cmd_arg, a, cmd, 1);
			}
			free(cmd_path);
			(1) && (cmd_path = ft_strjoin(a.s_path[i], cmd_arg),
					ft_freee(cmd), cmd = ft_split(cmd_path, ' '));
			return (free(cmd_path), cmd);
		}
		free(cmd_path);
		i++;
	}
	return (ft_freee(cmd), NULL);
}

char	**cmd_path(char *cmd_arg, t_all a)
{
	char	**cmd;
	char	*cmd_path;

	cmd_path = NULL;
	cmd = ft_split(cmd_arg, ' ');
	if (cmd)
	{
		if (ft_strchr(cmd[0], '/'))
			return (cmd);
		return (path_finder(cmd_arg, a, cmd_path, cmd));
	}
	return (ft_freee(cmd), NULL);
}
