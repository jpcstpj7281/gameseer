call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe debug
copy ac1608.xml debug/ac1608.xml
