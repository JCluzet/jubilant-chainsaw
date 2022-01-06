/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lettre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 18:13:44 by jcluzet           #+#    #+#             */
/*   Updated: 2022/01/06 19:44:57 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#define BUFFER_SIZE 10
#define KEEPALL 1

typedef struct s_gnl
{
	char buff[BUFFER_SIZE + 1];
	int ret;
	int index;
} t_gnl;

int get_next_line(int fd, char **line);
char *ft_strjoin(char **line, char *buff);
int readfile(int fd, char *buff, char *str);
char get_this_line(int fd, char **line, t_gnl gnl);
char *ft_strdup(const char *s);
int ft_strchr(char *buff);
int ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char *ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char *ft_strdup(const char *s)
{
	char *moulitruc;
	int i;
	int u;

	i = 0;
	u = (int)ft_strlen(s);
	moulitruc = malloc(sizeof(char) * u + 1);
	if (moulitruc == NULL)
		return (NULL);
	while (s[i])
	{
		moulitruc[i] = s[i];
		i++;
	}
	moulitruc[i] = '\0';
	return (moulitruc);
}

char *ft_strjoin(char **line, char *buff)
{
	char *tmp;
	int i;
	int u;

	i = ft_strlen(buff);
	if (!(tmp = malloc(i + ft_strlen(*line) + 1)))
		return (NULL);
	i = 0;
	u = 0;
	while ((*line)[u])
	{
		tmp[i] = (*line)[u];
		i++;
		u++;
	}
	u = 0;
	while (buff[u])
	{
		tmp[i] = buff[u];
		i++;
		u++;
	}
	free((char *)*line);
	tmp[i] = '\0';
	return (tmp);
}

int ft_strchr(char *buff)
{
	int index;

	index = 0;
	while (buff[index])
	{
		if (buff[index] == '\n')
			return (0);
		index++;
	}
	return (1);
}

int readfile(int fd, char *buff, char *str)
{
	int ret;

	if (str)
	{
		ft_strcpy(buff, str);
		free(str);
		return (1);
	}
	ret = read(fd, buff, BUFFER_SIZE);
	buff[ret] = '\0';
	return (ret);
}

char get_this_line(int fd, char **line, t_gnl gnl)
{
	static char *str;

	*line = ft_strdup("");
	while ((gnl.ret = (readfile(fd, gnl.buff, str))) > 0)
	{
		if (str)
			str = NULL;
		if (!(ft_strchr(gnl.buff)))
		{
			gnl.index = 0;
			while (gnl.buff[gnl.index] != '\n')
				gnl.index++;
			gnl.buff[gnl.index] = '\0';
			if (!str)
				str = ft_strdup(gnl.buff + gnl.index + 1);
			*line = ft_strjoin(line, gnl.buff);
			return (1);
		}
		else
			*line = ft_strjoin(line, gnl.buff);
	}
	if (*line == NULL)
		*line = ft_strdup("");
	return (gnl.ret);
}

int get_next_line(int fd, char **line)
{
	t_gnl gnl;

	gnl.index = 0;
	if (!line || BUFFER_SIZE < 1 || read(fd, gnl.buff, 0) < 0)
		return (-1);
	return (get_this_line(fd, line, gnl));
}

//--------------------------------------------------------------------

int cando(char *str, char *buffer)
{
	int strvide[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int i = 0;
	int j = 0;
	while (buffer[i] != '\0')
	{
		j = 0;
		while (j < 10)
		{
			if ((buffer[i] == str[j]) && (strvide[j] == 0))
			{
				strvide[j] = 1;
				i++;
				j = -1;
			}
			j++;
			if (j == 0 && buffer[i] == '\0')
			{
				return (i);
			}
			else if (j == 10)
			{
				return (-1);
			}
		}
	}
	return (i);
}

int good(char *str)
{
	int i = 0;
	char *buffer;
	char *bufferr;
	int lastcount = 0;
	int ret;
	int j = 0;
	int count = 0;
	int fd = open("dico.txt", O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &buffer);
		// set buffer in minuscule
		while (buffer[j] != '\0')
		{
			if (buffer[j] >= 'A' && buffer[j] <= 'Z')
				buffer[j] = buffer[j] + 32;
			j++;
		}
		j = 0;
		if ((cando(str, buffer) != -1))
		{
			if (KEEPALL == 1 || (ft_strlen(buffer) > lastcount))
			{
				printf("%s\n", buffer);
				if (ft_strlen(buffer) > lastcount)
				{
					lastcount = ft_strlen(buffer);
					bufferr = ft_strdup(buffer);
				}
			}
		}
		i++;
	}
	printf("\n\nMAX LETTERS FIND : %d\nWITH > %s\n", lastcount, bufferr);
	return (0);
}

int main(int argc, char **argv)
{
	char stock[11];
	if (argc != 11 && argc != 2)
	{
		printf("Please enter 10 letters\n");
		return (0);
	}
	if (argc == 2 && ft_strlen(argv[1]) != 10)
	{
		printf("Please enter 10 letters\n");
		return (0);
	}
	int i = 0;
	if (argc == 11)
	{
		while (i < 10)
		{
			stock[i] = *argv[i + 1];
			if (stock[i] > 64 && stock[i] < 91)
				stock[i] += 32;
			i++;
		}
	}
	if (argc == 2)
	{
		// store the 10 letters in stock
		while (i < 10)
		{
			stock[i] = argv[1][i];
			if (stock[i] > 64 && stock[i] < 91)
				stock[i] += 32;
			i++;
		}
	}
	stock[i] = '\0';
	good(stock);
}
