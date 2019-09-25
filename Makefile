CC=gcc  #compiler
TARGET=shell #target file name
 
all:	shell.c display.c parsing.c changedir.c pwd.c echo.c execute.c pinfo.c ls.c history.c writehistory.c setenv.c unsetenv.c piping.c redirection.c execute2.c
		$(CC) shell.c parsing.c display.c changedir.c pwd.c echo.c execute.c pinfo.c ls.c history.c  writehistory.c setenv.c unsetenv.c piping.c redirection.c execute2.c -lreadline -o $(TARGET)
 
clean:
		rm $(TARGET) .history