# Run the command make all to create the shell.
# The shell is present in the executable file "shell"
# Display :
    <user_name @ sys_name : cwd>
    ~ is the place where the executable shell is present.
# ls:
    ls <directory name> -a -l
    the flags and the directory name can be given in any order.
    Even ~ related paths can be given.
# cd: 
    cd <directory name>
    if the directory exits then it changes the directory to the one provided.
# echo:
    echo <anything>
    prints out the string given removing the extra spaces in between.
# pwd:
    pwd
    prints the pwd of the shell.
# pinfo:
    pinfo <pid>
    if no pid is provided , the pinfo of the shell is printed.
    for a given pid , the required info is printed.
# processess:
    bg - if the processess are given without & at the end , the process is run and shell waits till it's completion.
    fg - it prints the pid of the process that is just made.
         after the process ends, it gives info about the process that ended and the exit status.
# ';' seperated command:
    many commands can be given seperated by a ';' and there are run sequentially.
# history:
    history <Number>
    gives the latest (<=)10 commands entered in the shell.
    given Number(<=10) , it prints that many number of latest commands from history.
