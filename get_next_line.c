/* header */

#include "get_next_line.h"

static char *read_from_file(int fd, char *remainder, char *buffer)
{
    int rlen;
    char *temp;
    
    rlen = 1;
    while(rlen > 0)
    {
        rlen = read(fd, buffer, BUFFER_SIZE);
        if (rlen == -1)
        {
            free(remainder);
            return (NULL);
        }
        else if (rlen == 0)
            break;
        buffer[rlen] = '\0';
        temp = remainder;
        remainder = ft_strjoin(temp, buffer);
        free(temp);
		if(ft_strchr(buffer, '\n'))
			break;
    }
    if (*remainder == 0 || !remainder)
    {
        free(remainder);
        remainder = NULL;
        return(NULL);
    }    
    return (remainder);
}

static char *extract_line(char *remainder)
{
    size_t i;

    i = 0;
	if (!remainder[i])
		return (NULL);
    while(remainder[i] && remainder[i] != '\n')
        i++;
    if(remainder[i] == '\n')
        i++;
    return ft_substr(remainder, 0, i);
}

static char *remove_unwanted(char *remainder)
{
    char *new_remainder;
    size_t i;

    i = 0;
    while(remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	i++;
	if (remainder[i] == '\0')
    {
        free(remainder);
        return NULL;
    }
	new_remainder = ft_strdup(remainder + i);
    free(remainder);
    return(new_remainder);
}

char *get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    char *temp;
	
    if (!remainder)
	remainder = ft_strdup("");
    
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);

	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
		free(remainder);
		free(buffer);
		buffer = NULL;
		remainder = NULL;
		return (NULL);
	}   
	
	remainder = read_from_file(fd, remainder, buffer);
	free(buffer);

	if (!remainder || *remainder == '\0')
	{
        free(remainder);
        remainder = NULL;
        return NULL;
    }
    temp = extract_line(remainder);
	remainder = remove_unwanted(remainder);

    return(temp);
}