/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:13:12 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/29 14:48:54 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compare the first (at most) n bytes (interpreted as unsigned char) of the
memory areas s1 and s2. Return an int indicating the result of the comparison:
	• 0 if the memory blocks match;
	• a negative int if s1 is less than s2;
	• a positive int if s1 is greater than s2;
The non-zero value and its sign are determined by the difference in the ASCII
values of the first two non-equal characters.  

Note that we must cast the return value to an unsigned char (if char is signed,
chars with values greater than 127 will be negative; since regular chars are 8
bits, they can represent values from -128 to 127; an unsigned char can represent
values from 0 to 255. 

Also note that since the function must return an int, it automatically promotes
char to int in the if-else conditions; however, casting to int is important in
the final return value to ensure that the subtraction is done correctly. */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*byte_ptr1;
	unsigned char	*byte_ptr2;

	byte_ptr1 = (unsigned char *)s1;
	byte_ptr2 = (unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	while (n > 1 && *byte_ptr1 == *byte_ptr2)
	{
		byte_ptr1++;
		byte_ptr2++;
		n--;
	}
	return ((int)(*byte_ptr1) - (int)(*byte_ptr2));
}

/* #include <stdio.h> 
int main(void)
{
	const char *str1 = "Hello, world0";
	const char *str2 = "Hello, world";
	size_t n = 13;

	int result = ft_memcmp(str1, str2, n);
	if (result == 0)
		printf("The first %ld bytes are identical.\n", n);
	else
		printf("Difference between the first non-identical bytes:%d\n", result);
	return (0);
} */
