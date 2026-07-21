/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:18:36 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 16:56:36 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

void	*ma_routine(void *arg)
{
	int val;
	val = *(int *)arg;
	printf("Bonjour, je suis un thread %d!\n", val);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread[5];
	int	val[5];
	int i;
	int j;
	
	i = 0;
	while (i < 5)
	{
		val[i] = i + 1;
		pthread_create(&thread[i], NULL, ma_routine, &val[i]);
		i++;
	}
	
	printf("Le thread a fini, main se termine.\n");
	i = 0;
	while (i < 5)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	printf("Le thread a fini, main se termine.\n");
	return (0);
}