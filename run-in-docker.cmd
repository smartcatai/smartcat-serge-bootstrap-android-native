@echo off
echo Mounting %~dp0 as /data

docker run ^
    --rm ^
    -v "%~dp0:/data" ^
    -v "%~dp0/.ssh:/tmp/.ssh" ^
    --entrypoint ./boot/run-in-docker.sh ^
    smartcatcom/serge ^
    %*
