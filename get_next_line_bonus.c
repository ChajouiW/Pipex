/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:07:50 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/30 21:04:44 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*new_line(char *s)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			if (s[i] == '\n')
				return ((char *)(s + i));
			i++;
		}
	}
	return (NULL);
}

static char	*no_newline(char **l3mara)
{
	char	*line;

	line = ft_strdup(*l3mara);
	free(*l3mara);
	*l3mara = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*l3mara;
	char		*line;
	char		*new_l;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	l3mara = t3mar(fd, &l3mara);
	new_l = new_line(l3mara);
	if (new_l)
	{
		line = ft_substr(l3mara, (new_l - l3mara + 1));
		new_l = ft_strdup(new_l + 1);
		free(l3mara);
		if (*new_l == '\0')
		{
			free(new_l);
			l3mara = NULL;
		}
		else
			l3mara = new_l;
	}
	else
		line = no_newline(&l3mara);
	return (line);
}
