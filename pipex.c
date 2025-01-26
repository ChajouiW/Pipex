/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:55:23 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/23 16:34:24 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!big || !little) && len == 0)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}



int	check_infile()
{
	/*if (fd = open(av[1], O_RDONLY) && fd == -1)
	{
		if (access(av[1], F_OK) == -1)
			sir_t2awd();
		else if (access(av[1], R_OK) == -1)
		{
			perror("Permision");
			exit(1);
		}
	}*/
	return fd;
}

char	*check_envp()
{
	int	i;
	char	*s;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			s = ft_strnstr(envp[i], "PATH=", 5);
			break;
		}
		i++;
	}
	return (s);
}

int	main(int ac, char **av, char **envp)
{
	int	fd;

	if (ac == 5)
	{
		pid_t	pid = fork();
		if (pid == 0)
		{
			int fd = check_infile(av[1]);
			char	**ss = ft_split(check_envp(envp), ':');
			s = ft_split(av[2], ' ');
			if (ft_strchr(s, '/'))
			{
				if (access(s, F_OK | X_OK) == -1)
					ghayrha();
				else
					if(execve(s[0], s, envp);
			}
			else
				for(int j = 0; ss[j];j++)
				{
					if (j == 0)
						s = ft_strjoin(&ss[j][5], s[0]);
					else
						s = ft_strjoin(ss[j], av[2]);
					if (access(s, F_OK | X_OK) != -1)
				}
	}
}
