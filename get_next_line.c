/* header */

#include "get_next_line.h"

static char *read_from_file(int fd, char *remainder, char *buffer)
{
    int rlen;
    char *temp;
    
    rlen = 1;
    while(!ft_strchr(remainder,'\n') && rlen > 0)
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
    char *temp;
    size_t i;

    i = 0;
    while(remainder[i] && remainder[i] != '\n')
        i++;
    if(remainder[i] == '\n')
        i++;
    temp = ft_calloc(i + 1, sizeof(char));
    if (!temp)
        return(NULL);
    ft_strlcpy(temp, remainder, i + 1);
    return (temp);
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
    if(remainder[i] == '\n')
        i++;
    
    new_remainder = ft_strdup(&remainder[i]);
    free(remainder);
    return(new_remainder);
}

char *get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    char *temp;
    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    if (!remainder)
        remainder = ft_strdup("");
    
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	
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