/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:16:44 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/30 14:50:28 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* A special case strlen for when dest is NOT nil-terminated. Return the length
of dest bound by size. */
static size_t	special__strlen(char *dest, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && dest[i])
	{
		i++;
	}
	return (i);
}

/* Append at most (size - dest_len - 1) bytes of src to the end of dest; the
result will be NUL-terminated as long as there is at least one byte free in dest.
Return the total length of the string that was attempted to be created (in this
case, the initial length of dest + the length of src; however, if size is less
than or equal to dest, return size + src_len). 

Return the initial length of dest + the length of src. */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	limit;
	size_t	i;

	dest_len = special__strlen(dest, size);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	limit = size - dest_len - 1;
	i = 0;
	while (i < limit && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/* #include <stdio.h>
int	main(void)
{
	char	*source = "bob";
	char	destination[10] = "hello ";
	size_t	result;

	printf("Before: %s\n", destination);
	result = ft_strlcat(destination, source, 10);
	printf("After:  %s\n", destination);
	printf("Returned length: %ld\n", result);
	return (0);
} */
