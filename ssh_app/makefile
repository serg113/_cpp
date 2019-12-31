
LIB_VS=..\ssh_library
APP_DIR = .\ssh_app.exe

ssh_app: main.obj Session.obj
		link /out:$(APP_DIR) $(LIB_VS)\*.lib  .\*.obj 
		 
main.obj: ..\main.cpp ..\Session.h 
		cl /c /EHsc ..\main.cpp   
		
Session.obj: ..\Session.cpp ..\Session.h $(LIB_VS)/libssh/libssh.h $(LIB_VS)/libssh/sftp.h
		cl /c /EHsc ..\Session.cpp 

clean: 
		del *.obj
