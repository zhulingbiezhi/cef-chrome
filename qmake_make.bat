@echo off
set CurDir=%~dp0
set QCefViewDir=%CurDir%\sourceCode\QCefView\
set QCefViewHelperDir=%CurDir%\sourceCode\QCefViewHelper\
set QCefViewTestDir=%CurDir%\sourceCode\QCefViewTest\


echo qmake QCefView start...
cd /d %QCefViewDir%
qmake -tp vc
echo qmake QCefView finished

echo qmake QCefViewHelper start...
cd /d %QCefViewHelperDir%
qmake -tp vc
echo qmake QCefViewHelper finished

echo qmake QCefViewTest start...
cd /d %QCefViewTestDir%
qmake -tp vc
echo qmake QCefViewTest finished

echo qmake All start...
cd /d %CurDir%
qmake -tp vc
echo qmake All finished

pause