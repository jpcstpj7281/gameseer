mkdir ndll
cd ndll 
mkdir Windows
cd ..
cd project
mkdir ndll
cd ndll 
mkdir Windows
cd ..
haxelib run hxcpp Build.xml -DWindows
cd ..
cp project/ndll/Windows/* ndll/Windows/
