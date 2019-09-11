CC=gcc  #compiler
TARGET=shell #target file name
 
all:	shell.c display.c parsing.c changedir.c pwd.c echo.c execute.c pinfo.c ls.c history.c writehistory.c 
		$(CC) shell.c parsing.c display.c changedir.c pwd.c echo.c execute.c pinfo.c ls.c history.c  writehistory.c -o $(TARGET)
 
clean:
		rm $(TARGET) .history