#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir;
	char buffer[1024];

	if (!info->argv[1]) /* If no directory provided, change to home directory */
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = "/";
	}
	else if (_strcmp(info->argv[1], "-") == 0)
		/* If "-" provided,  change to previous directory */
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts("TODO: >>getcwd failure emsg here<<\n");
			return (1);
		}
		_puts(dir);
		_putchar('\n');
	}
	else /* Change to the specified directory */
	{
		dir = info->argv[1];
	}

	if (chdir(dir) == -1) /* Change directory and handle errors */
	{
		print_error(info, "can't cd to ");
		_eputs(dir);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - prints a help message (not yet implemented)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	(void)info; /* Avoid unused variable warning */
	_puts("Help function is not yet implemented.\n");
	return (0);
}
