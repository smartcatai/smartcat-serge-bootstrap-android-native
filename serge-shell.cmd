@echo off
echo Mounting %~dp0 as /data
docker run ^
    --rm ^
    -v "%~dp0:/data" ^
    -v "%~dp0/.ssh:/tmp/.ssh" ^
    -it ^
    --entrypoint ./boot/serge-shell.sh ^
    --env PS1="\[\033[01;35m\][Serge Shell]\[\033[00m\] \w \$ " ^
    smartcatcom/serge
