
LIB_SSH = ..\ssh_library
APP = .\ssh_app.exe

ssh_app: main.obj session.obj
		link /out:$(APP) $(LIB_SSH)\ssh.lib  .\*.obj 
		 
main.obj: ..\main.cpp ..\session.h 
		cl /c /EHsc ..\main.cpp   
		
session.obj: ..\session.cpp ..\session.h $(LIB_SSH)\libssh\libssh.h $(LIB_SSH)\libssh\sftp.h
		cl /c /EHsc ..\session.cpp 

clean: 
		del *.obj
