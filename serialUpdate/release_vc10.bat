call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe release
cp config.xml release/