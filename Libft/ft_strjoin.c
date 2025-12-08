/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:22:34 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/24 11:46:03 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocate memory and return a new string that is the result of concatenating
s1 and s2. On failure, return NULL. Note +1 on malloc for \0. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	final_len;
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	final_len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc((final_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		result[i++] = s1[j++];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

/* #include <stdio.h>
int	main(void)
{
	char	*s1 = "Hello ";
	char	*s2 = "world!";
	char	*s3 = ft_strjoin(s1, s2);
	printf("s1: %s\ns2: %s\nTogether: %s\n", s1, s2, s3);
	free(s3);
	return (0);
} */
