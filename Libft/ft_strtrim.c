/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:47:49 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/30 14:57:45 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return 1 if c is anywhere in set; 0 otherwise. */
static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

/* Allocate memory and return a copy of s1 with characters from set removed from
the beginning and the end. If the whole string is trimmed, give an empty one. */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;
	char	*trimmed_s;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && is_in_set(s1[end], set))
		end--;
	len = end - start + 1;
	trimmed_s = (char *)malloc(len + 1);
	if (!trimmed_s)
		return (NULL);
	i = -1;
	while (++i < len)
		trimmed_s[i] = s1[start + i];
	trimmed_s[len] = '\0';
	return (trimmed_s);
}

/* #include <stdio.h>
int	main(void)
{
	char	*s1 = "";
	char	*set = "a";
	char	*trim = ft_strtrim(s1, set);
	printf("Trimmed string: %s\n", trim);
	return (0);
} */
