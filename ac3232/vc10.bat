call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe debug
cp ac1608.xml Debug/ac1608.xml
cp -r ./res ./Debug/
cp lib/qwtd.dll Debug/
