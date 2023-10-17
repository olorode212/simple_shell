#include "shell.h"

/**
 * write_history_to_file - writes history to a file
 * @info: parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history_to_file(info_t *info)
{
       	char *filename = get_history_file(info);
       
	if (!filename)
	{
	       	{return -1; }
	}
	
	ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(filename);
	if (fd == -1)
	{
		{return -1; }
	}
	list_t *node = info->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	{return 1; }
}

/**
 * read_history_from_file - reads history from a file
 * @info: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history_from_file(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
	{
		{return 0; }
	}
	ssize_t fd = open(filename, O_RDONLY);

	free(filename);
	if (fd == -1)
	{
		{return 0; }
	}
	struct stat st;
	if (fstat(fd, &st) == -1 || st.st_size < 2)
	{
		close(fd);
		{return 0; }
	}
	
	char *buf = malloc(st.st_size + 1);
	if (!buf)
	{
	       	close(fd);
		{return 0; }
	}
	ssize_t rdlen = read(fd, buf, st.st_size);
	close(fd);
	if (rdlen <= 0)
	{
		free(buf);
		{return 0; }
	}
	buf[st.st_size] = '\0';
	int last = 0;
	int linecount = 0;
	
	for (int i = 0; i < st.st_size; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			if (info->history)
			{
				list_t *node = info->history;
				while (node->next)
				{
					node = node->next;
				}
				node->next = create_node(buf + last, linecount++);
			}
			else
			{
                info->history = create_node(buf + last, linecount++);
            }
            last = i + 1;
        }
    }

    free(buf);
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
    {
        delete_node_at_index(&(info->history), 0);
    }

    {return renumber_history(info); }
}
