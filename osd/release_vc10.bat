call "%VS100COMNTOOLS%/vsvars32.bat"
call nmake.exe release
copy osd.xml release/osd.xml
