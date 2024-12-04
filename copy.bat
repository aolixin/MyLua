@echo off
set src_path=E:\projects\cpp_proj\LuaTest\lua-5.4.7\src
set dest_path=E:\projects\cpp_proj\LuaTest\LuaTest\include
set vcffile=*.hpp
E:
cd %src_path%
for /f "delims=" %%s in ('dir /b/a-d/s "%src_path%"\"%vcffile%"') do (
echo %%s
copy /y "%%s" %dest_path%
)
pause
