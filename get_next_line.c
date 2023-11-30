/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:18:30 by agallon           #+#    #+#             */
/*   Updated: 2023/11/23 19:18:33 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// read close
#include <stdio.h>	// printf malloc free
#include <stdlib.h> // malloc free
#include <fcntl.h>	// open
#include "get_next_line.h"

// # 	STATIC BUFFER
static char	g_temp[BUFFER_SIZE] = {'\0'};

///////////////////////////////////////////////////////
// #	RETURN CLEAN NODE, IF FIRST NODE, FILL WITH TEMP
t_list	*ini_node(t_list *first_list)
{	
	t_list	*next_list;
	t_list	*current_list;
	int		i;

	current_list = first_list;
	next_list = (t_list *)malloc(sizeof(t_list));
	if (!next_list)
		return (NULL);
	clean_buff(next_list->buff, 0);
	next_list->next = NULL;
	if (first_list != NULL)
	{
		while (current_list->next != NULL)
			current_list = current_list->next;
		current_list->next = next_list;
	}
	else
	{
		i = 0;
		while (i++ < BUFFER_SIZE)
			next_list->buff[i - 1] = g_temp[i - 1];
	}
	return (next_list);
}

////////////////////////////////////////[0000][0123][4\n56]
// #	RETURN RESULT	1 > 2
char	*f_rtrn_2(t_list *first_list, char *rtrn, int size)
{
	t_list	*current_list;
	int		i;
	int		j;

	i = 0;
	j = 0;
	current_list = first_list;
	while (j < size)
	{
		if (i == BUFFER_SIZE || current_list->buff[i] == '\0')
		{
			current_list = current_list->next;
			i = 0;
		}
		if (current_list->buff[i] != '\0')
			rtrn[j++] = current_list->buff[i];
		i++;
	}
	rtrn[j] = '\0';
	return (rtrn);
}

////////////////////////////////////////
char	*f_rtrn_1(t_list *first_list, int fd)
{
	int		size;
	char	*rtrn;

	size = rtrn_size(first_list, fd);
	if (size <= 0)
		return (NULL);
	rtrn = (char *)malloc(size + 1);
	if (!rtrn)
		return (NULL);
	rtrn = f_rtrn_2(first_list, rtrn, size);
	return (rtrn);
}

///////////////////////////////////////////////////////
// #	RESET TEMP = COPY THE REMAINDER TO TEMP
void	f_copy_rest(t_list *last_list)
{
	int	i;
	int	size;

	clean_buff(g_temp, 1);
	size = is_there_n(last_list);
	i = 0;
	if (size > 0)
	{
		while (i++ + size < BUFFER_SIZE && \
							last_list->buff[size + i - 1] != '\0')
			g_temp[i - 1] = last_list->buff[size + i - 1];
	}
	else if (size == 0)
		return ;
	else if (size < 0)
	{
		while (i - size < BUFFER_SIZE && last_list->buff[i - size] != '\0')
		{
			g_temp[i] = last_list->buff[i - size];
			i++;
		}
	}
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
char	*get_next_line(int fd)
{
	t_list	*first_list;
	t_list	*current_list;
	char	*rtrn;

	first_list = ini_node(NULL);
	if (!first_list)
		return (NULL);
	rtrn = f_rtrn_1(first_list, fd);
	if (rtrn == NULL)
	{
		free_all(&first_list);
		return (NULL);
	}
	current_list = first_list;
	while (current_list->next != NULL)
		current_list = current_list->next;
	f_copy_rest(current_list);
	free_all(&first_list);
	return (rtrn);
}
/*
int main()
{
    int fd = open("txt.txt", 0);
    if (fd == -1)
    {
        printf("error opening");
        return 0;
    }

    char *nextline = get_next_line(fd);
    int i = 1;

    while (nextline != NULL)
    {
        printf("Line num:%d = ", i);

        // Print the ASCII values of each character in the line
        for (int j = 0; nextline[j] != '\0'; j++)
        {
            printf("%d ", nextline[j]);
        }

        printf("\n");

        i++;
        free(nextline);
        nextline = get_next_line(fd);
    }

    free(nextline);
    close(fd);
    return 0;
}*/
/*
int	main()
{
	int	fd = open("txt.txt", 0);
    if (fd == -1)
    {
        printf("error opening");
        return 0;
    }
    //printf("TEMP start = %s\n", g_temp);
    char *nextline = get_next_line(fd);
    //free(nextline);
    int	i = 1;
  
    while (nextline != NULL)
    {
  		//printf("TEMP = %s\n", g_temp);
  		printf("line num:%d = %s", i, nextline);
  		i++;
  		free(nextline);
  		nextline = get_next_line(fd);
  	}
  	//printf("TEMP = %s\n", g_temp);
  	printf("line num:%d = %s", i, nextline);
  	free(nextline);
	close(fd);
	return 0;
}*/
