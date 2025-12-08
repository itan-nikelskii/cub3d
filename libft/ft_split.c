/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:33:43 by inikelsk          #+#    #+#             */
/*   Updated: 2025/05/03 10:55:29 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Count non-empty substrings separated by delimiter c. Multiple consecutive 
delimiters are treated as one. Return substring count. */
static int	count_substrings(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

/* Find and return the length of a substring. A substring is delimited by c. */
static int	substring_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

/* Free each element of the array and then the array itself. Notice
arr[i] = NULL - this is to avoid double free errors in the future. */
static void	free_all(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}

/* Iterate over s until the beginning of a valid substring is found; find the
length of that substring, allocate enough memory and put it as an element of
the 'result' array. If allocation fails, free the entire array. Add a NULL
pointer at the end to signify the end of the array (will be the only element
if no valid substrings are found). */
static char	**fill_array(char const *s, char c, char **result)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c)
			start++;
		if (s[start])
		{
			len = substring_len(s + start, c);
			result[i] = ft_substr(s, start, len);
			if (!result[i])
			{
				free_all(result, i - 1);
				return (NULL);
			}
			start += len;
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}

/* Return an array of strings obtained by splitting ’s’ using ’c’ as delimiter. 
The array ends with a NULL pointer (hence + 1 on malloc). On success, return the
array of substrings resulting from the split. On fail, return NULL. */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;

	if (!s)
		return (NULL);
	count = count_substrings(s, c);
	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (fill_array(s, c, result));
}

/* #include <stdio.h>
int	main(void)
{
	char	*test_str = ",Hello,,world,,this,is,a,test,,,!";
	char	c = '&';

	char	**result = ft_split(test_str, c);
	if (result == NULL)
	{
		printf("Memory allocation failed.\n");
		return (1);
	}
	int	i = 0;
	while (result[i] != NULL)
	{
		printf("Substring %d: %s\n", i, result[i]);
		i++;
	}
	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
} */
