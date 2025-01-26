/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:23:29 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/25 22:02:55 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(char *file_name, int in_out)
{
	int	fd;

	if (in_out == 0)
	{
		if (access(file_name, F_OK) == -1)
			return (ft_printf("no such file or directory: %s\n", file_name), -1);
		if (access(file_name, R_OK) == -1)
			return (ft_printf("permission denied: %s\n", file_name), -1);
	//	fd = open("/dev/null", O_RDONLY);
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
			else
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

char	**cmd_path(char *cmd_arg, char **path)
{
	char	**cmd;
	char	*tmp;
	char	*cmd_path;
	int	i;

	cmd = ft_split(cmd_arg, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd_arg, '/'))
		return (cmd);
	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd[0]);
		if (!cmd_path)
			break ;
		if (!access(cmd_path, F_OK | X_OK))
		{
			tmp = ft_strjoin(path[i], cmd_arg);
			ft_freee(cmd);
			cmd = ft_split(tmp, ' ');
			return (free(cmd_path), free(tmp), cmd);
		}
		free(cmd_path);
		i++;
	}
	ft_freee(cmd);
	return (NULL);
}
