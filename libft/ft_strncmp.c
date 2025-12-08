/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:26:41 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/23 14:20:12 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compare the first (at most) n bytes of s1 and s2 in both strs; return an int
indicating the result of the comparison, as follows:
	• 0 if s1 and s2 are equal OR n is less than 1;
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
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while (*s1 && *s1 == *s2 && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

/* #include <stdio.h> 
int main(void) 
{  
	char	*s1 = "hello";
	char	*s2 = "hello";
	if (ft_strncmp(s1, s2, 5) == 0)
		printf("The strings are equal.\n");
	else   
		printf("The strings are NOT equal (%i).\n", ft_strncmp(s1, s2, 5));
   return (0);
}  */
