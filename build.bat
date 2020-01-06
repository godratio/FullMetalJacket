call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set CommonCompilerFlags= -F10485760 -I -std:c++14 -guard:cf -EHsc -arch:AVX -GR- -MTd -nologo -fp:fast -Gm- -GR- -GS- -sdl- -EHa- -Od -Oi -WX -W4 -wd4457 -wd4018 -wd4459 -wd4389 -wd4312 -wd4245 -wd4996 -wd4201 -wd4100 -wd4506 -wd4127 -wd4189 -wd4505 -wd4577 -wd4101 -wd4702 -wd4456 -wd4238 -wd4244 -wd4366 -wd4700 -wd4701 -wd4703 -wd4805 -wd4091 -wd4706 -wd4197 -wd4324 -DWINDOWS=1  -FC -Z7 
set CommonLinkerFlags=  -incremental:no -opt:ref Kernel32.lib user32.lib gdi32.lib winmm.lib Ws2_32.lib Ole32.lib Xinput9_1_0.lib DXGI.lib D3D12.lib D3DCompiler.lib

set CommonCompilerFlagsNoLink = -F10485760 -I -std:c++14 -guard:cf -EHsc -arch:AVX -GR- -MTd -nologo -fp:fast -Gm- -GR- -GS- -sdl- -EHa- -Od -Oi -WX -W4 -wd4457 -wd4018 -wd4459 -wd4389 -wd4312 -wd4245 -wd4996 -wd4201 -wd4100 -wd4506 -wd4127 -wd4189 -wd4505 -wd4577 -wd4101 -wd4702 -wd4456 -wd4238 -wd4244 -wd4366 -wd4700 -wd4701 -wd4703 -wd4805 -wd4091 -wd4706 -wd4197 -wd4324 -DWINDOWS=1  -FC -Z7 

IF NOT EXIST build mkdir build
pushd build
del *.pdb > NUL 2> NUL
echo WAITING FOR PDB > lock.tmp
del lock.tmp

REM build a FMJ lib than have the test app run that for quick testing.
cl -c %CommonCompilerFlagsNoLink%  ../fmj.cpp   -Fmfmj.map
lib fmj.obj

REM build the test app.
REM cl %CommonCompilerFlags%  ../main.cpp   -Fmmain.map /link -incremental:no -opt:ref -PDB:main.pdb %CommonLinkerFlags%
popd
