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
int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);

if (fd == -1)
{
{return -1; }
}
write_history_entries(info, fd);
close(fd);
{return 1; }
}
void write_history_entries(info_t *info, int fd)
{
list_t *node = info->history;

while (node)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
node = node->next;
}
_putfd(BUF_FLUSH, fd);
}
int read_history_from_file(info_t *info)
{
char *filename = get_history_file(info);

if (!filename)
{
{return 0; }
}
int fd = open(filename, O_RDONLY);
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
char *buf = read_history_content(fd, st.st_size);
close(fd);

if (!buf)
{
{return 0; }
}
process_and_store_history(info, buf, st.st_size);
free(buf);

{return renumber_history(info); }
}
char *read_history_content(int fd, off_t size)
{
char *buf = malloc(size + 1);

if (!buf)
{
{return NULL; }
}
ssize_t rdlen = read(fd, buf, size);

if (rdlen <= 0)
{
free(buf);
{return NULL; }
}
buf[size] = '\0';
{return buf; }
}
void process_and_store_history(info_t *info, char *buf, int size)
{
int last = 0;
int linecount = 0;

for (int i = 0; i < size; i++)
{
if (buf[i] == '\n')
{
buf[i] = '\0';
add_history_entry(info, buf + last, &linecount);
last = i + 1;
}
}
info->histcount = linecount;

while (info->histcount-- >= HIST_MAX)
{
delete_node_at_index(&(info->history), 0);
}
}
void add_history_entry(info_t *info, char *entry, int *linecount)
{
if (info->history)
{
list_t *node = info->history;
while (node->next)
{
node = node->next;
}
node->next = create_node(entry, (*linecount)++);
}
else
}
info->history = create_node(entry, (*linecount)++);
}
}
