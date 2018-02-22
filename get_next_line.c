/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:51:33 by schakor           #+#    #+#             */
/*   Updated: 2018/02/20 17:13:40 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_backslashn_chr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		++i;
	}
	return (-1);
}

char	*my_realloc(char *str, int size)
{
	char 	*ret;

//	printf("myrealloc\n");
	//len = ft_strlen(str);
//	printf("realloc len\n");
	if (!str)
	{
		if ((!(str = (char *)malloc(sizeof(*str) * (size + 1)))))
			return (NULL);
		return (str);
	}
	//if (len > size || !str)
	//{
	//	printf("str = %s\nlen = %d | size = %d\n", str, len, size);
//		return (NULL);
//	}
//	printf("realloc if\n");
	if (!(ret = (char *)malloc(sizeof(*ret) * (size + 1))))
	{
//		printf("!ret\n");
		return (NULL);
	}
//	printf("realloc after malloc\n");
	ft_strcpy(ret, str);
//	printf("realloc strcpy\n");
	free(str);
//	printf("realloc end\n");
	return (ret);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char		*ret;

//	printf("strjoin start\n");
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(*ret) * (ft_strlen(s1) + ft_strlen(s2)
						+ 1))))
		return (NULL);
//	printf("strjoin after if\n");
	ft_strcpy(ret, s1);
//	printf("strjoin after strcpy\n");
	ft_strcat(ret, s2);
//	printf("strjoin after strcat\n");
	free(s1);
//	printf("strjoin end\n");
	return (ret);
}

char	*ft_strfadd(char *s1, char *s2, int i)
{
	int	a;
	char	*ret;
	char	c;
	a = 0;
//	printf("\n ||| strfadd ||| \n\n");
//	printf("%s\n",s2);
	while (s1[a])
		a++;
//	printf("a = %d\n", a);
	c = s2[i];
	s2[i] = '\0';
//	printf("%s\n",s2);
	ret = ft_strfjoin(s1, s2);
	s2[i] = c;
//	j = 0;
//	while (j < (i + a))
//	{
//		s1[a++] = s2[i++];
//		j++;
//	}
//	printf("end while\n");
	ret[a + i] = '\0';
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static char		*over = NULL;
	char			buf[BUFF_SIZE + 1];
//	char			*str;
	int				rd;
	int				i;
	int				size;


	size = 0;
	if (fd == -1)
	{
		//printf("fd = -1\n");
		return (-1);
	}
	if (*line)
	{
		//printf("%s\n",*line);
		if ((i = ft_backslashn_chr(over)) != -1)
		{
			*line = ft_strsub(over, 0, i);
//			printf("line = %s\nover = %s\n",*line,over);
			over = ft_strsub(over, i + 1, (BUFF_SIZE - i));
	//		printf("over = %s\n",over);
			if (over[0] == '\0')
			{
				free(over);
				return (0);
			}
	//		printf("1rd = %d\n",rd);
			return (1);
//			printf("over = %s\n",over);
		}
		else
		{
			*line = ft_strcpy(*line, over);
	//		printf("slt\n");
		}
	}
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
	//	printf("rd = %d\n",rd);
//		printf("starwhile\n");
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			if (size == 0)
				size += BUFF_SIZE;
	//		printf("size = %d\n",size);
		//	printf("%s\n", *line);
		//	printf("ici : %c\n", (*line)[size - 1]);	
		//	printf("back slash a i = %d\n",i);
			size -= i;
	//		printf("line = %s\nsize = %d | i = %d\nbuf = %s\n",*line,size,i,buf);
			*line = my_realloc(*line, size); 
			*line = ft_strfadd(*line, buf, i);
	//		printf("afterline\n");
			if (!over)
			{
		//		printf("malloc over\n");
				if (!((over = (char *)malloc(sizeof(char) * (i + 1)))))
					return (-1);
			}
			else
				free(over);
			over = ft_strsub(buf, i + 1, (BUFF_SIZE + 1) - i);
	//		printf("over = %s\n\n",over);
		//	printf("endGNL\n");
		//	printf("line = %s\n\nover = %s\n",*line,over);
		//	printf("%s\n",buf);
		//	printf("\n%s\n%s\n",buf,over);
			return (1);
		}
		size += BUFF_SIZE;
	//	printf("endwhile\n");
		*line = my_realloc(*line, size); 
		*line = ft_strfjoin(*line, buf);
	}
	//printf("afterwhile\n");
	//printf("rd2 = %d\n",rd);
	return (0);
}
int		main(int ac, char **av)
{
	char	*str;
	int		fd;
	int i =5;
	ac = 10;
	str = NULL;
	fd = open(av[1], O_RDONLY);
	while ((i > 0))
	{
		//printf("compteut = %d i = %d\n",cmt,i);
		//printf("%d\n", (i = get_next_line(fd, &str)));
		i = get_next_line(fd, &str);
		ft_putendl(str);
	}
	return (0);
}
