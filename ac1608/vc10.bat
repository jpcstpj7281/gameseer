cp ac1608.xml debug/ac1608.xml
cp -r ./res ./Debug/
call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe debug
