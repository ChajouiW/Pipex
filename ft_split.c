/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:24:39 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/28 17:46:07 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_word(char const *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else if (*s != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		s++;
	}
	return (count);
}

static char	*ft_t3mar(char const *s, char *word, char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		while (*s && *s == c)
			s++;
		word[i] = *s;
		i++;
		s++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free(char **arr, int word)
{
	while (word >= 0)
		free(arr[--word]);
	free(arr);
	return (NULL);
}

static char	**fill_arr(char **arr, char const *s, char c, int n_words)
{
	size_t	len;
	size_t	i;
	int		word_i;

	word_i = 0;
	while (word_i < n_words)
	{
		i = 0;
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		arr[word_i] = (char *)malloc(sizeof(char) * len + 1);
		if (!arr[word_i])
			return (ft_free(arr, word_i));
		arr[word_i] = ft_t3mar(s, arr[word_i], c, len);
		word_i++;
		s += i;
	}
	arr[word_i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		n_words;
	char	**arr;

	if (!s || !*s)
		return (NULL);
	n_words = count_word(s, c);
	arr = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!arr)
		return (NULL);
	return (fill_arr(arr, s, c, n_words));
}
