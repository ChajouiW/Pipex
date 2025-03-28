/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:16:37 by mochajou          #+#    #+#             */
/*   Updated: 2025/02/02 00:42:52 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_all	all;
	int		status;
	char	*tmp;

	if (ac != 5)
		usage(1);
	all.b = 0;
	all.ac = ac;
	all.envp = env;
	tmp = env_path(env);
	if (tmp)
		all.s_path = ft_split_cmd(tmp, ':');
	else
		all.s_path = ft_split_cmd("no path", ':');
	pipex(all, av, &status);
	while (wait(NULL) > 0)
		;
	ft_free(all.s_path, 0);
	exit(WEXITSTATUS(status));
}
