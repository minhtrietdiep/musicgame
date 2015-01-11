@echo off
rem Batch script to help with uploading Arduino sketches compiled by Visual Micro
rem By Thomas Schraven, (c) 2015

rem Currently Arduino boards with an ATmega328 chip are supported
rem Support for other AVR chips is added easily:
rem Check the verbose output of your programmer/uploader
rem and copy the avrdude command. Paste under :upload.

rem Don't forget to add the tools-settings.cfg file to your
rem .gitignore file, as the COM port is specific to your PC

cls
set projectpath=%cd%

if exist tools-settings.cfg (
    goto :hassettings
) else (
    goto :newsettings
)

:hassettings
set /p settings=<%projectpath%\tools-settings.cfg

setlocal EnableDelayedExpansion

set varName=
for %%a in (%settings%) do (
   if not defined varName (
      set varName=%%a
   ) else (
      set !varName!=%%a
      set varName=
   )
)

goto start

:newsettings
set /p port="Enter the port where your Arduino is connected (eg COM7): "

set i=0
for %%a in (*.ino) do set /a i+=1
if %i% GTR 1 goto toomanyfiles

for /r . %%g in (*.ino) do (
    set projectName=%%~ng
)

echo port=%port%,projectName=%projectName%>%projectpath%\tools-settings.cfg

goto start

:toomanyfiles
echo Multiple .ino files found.
set /p projectName="Enter the name of the main .ino file (aka project name): "
goto start

:start
set arduinoDir=C:\Program Files (x86)\Arduino
set buildpath=%userprofile%\AppData\Local\VMicro\Arduino\Builds\%projectName%\uno
set avrpath=hardware\tools\avr\bin
set elfpath=%buildpath%\%projectName%.elf
set hexpath=%buildpath%\%projectName%.hex

set CYGWIN=nodosfilewarning

cls
echo AVR CLI tools
echo Utility script to upload and check Arduino sketches built with Visual Micro
echo Arduino with ATmega328 on port %port%
echo.
echo Project: %projectName%
echo.

echo u to upload
echo a for avr-size

set /p choice="Make your choice (or e to exit): "

if "%choice%"=="a" goto avrsize
if "%choice%"=="u" goto upload
if "%choice%"=="e" goto instantexit

set message=No extra info
goto exit

:upload
cd %arduinoDir%
echo.
echo Uploading
"%avrpath%\avrdude" -C"%arduinoDir%\hardware\tools\avr\etc\avrdude.conf" -patmega328p -carduino -P\\.\%port% -b115200 -D -Uflash:w:%hexpath%:i
if errorlevel 0 set message=avrdude completed successfully
if errorlevel 1 set message=There was an error with avrdude
goto exit

:avrsize
cd %arduinoDir%
echo.
echo avr-size:
"%avrpath%\avr-size.exe" %elfpath%
if errorlevel 0 set message=avr-size completed successfully
if errorlevel 1 set message=There was an error with avr-size
goto exit

:exit
echo.
echo %message%
set /p exitchoice="Input t to choose another tool or anything else to exit: "

if "%exitchoice%"=="t" goto start

goto instantexit

:instantexit
echo Bye
cd %projectpath%