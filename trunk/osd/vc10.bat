cp osd.xml debug/osd.xml
cp -r ./res ./Debug/
call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe debug
