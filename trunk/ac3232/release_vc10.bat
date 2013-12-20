call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe 
copy ac1608.xml release/ac1608.xml
copy lib/qwt.dll release/
