
CC = cl
PARAMS = /c /EHsc
LIB_SSH = ..\ssh_library
APP = .\ssh_app.exe

ssh_app: main.obj session.obj argparser.obj
		link /out:$(APP) $(LIB_SSH)\ssh.lib  .\*.obj 
		 
main.obj: ..\main.cpp ..\session.h ..\argparser.h 
		$(CC) $(PARAMS) ..\main.cpp   
		
session.obj: ..\session.cpp ..\session.h $(LIB_SSH)\libssh\libssh.h $(LIB_SSH)\libssh\sftp.h
		$(CC) $(PARAMS) ..\session.cpp 
		
argparser.obj: ..\argparser.cpp ..\argparser.h 
		$(CC) $(PARAMS) ..\argparser.cpp

clean: 
		del *.obj