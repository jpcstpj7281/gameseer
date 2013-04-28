cp config.xml debug/
cp -r ./res ./Debug/
call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe debug
