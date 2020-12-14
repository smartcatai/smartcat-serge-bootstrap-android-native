#!/bin/sh

while true
do
    ./sync-once.sh

    echo "Sleeping for 5 minutes before the next cycle (press Ctrl+C to quit)"
    sleep 600
done
