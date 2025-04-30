#!/bin/bash
# Remove old revisions of snaps
# Make sure that snaps (like snap-store) are disabled

echo "Following snaps to be removed: "
snap list --all | awk '/disabled/{print $1}' |
    while read snapname; do
        echo " $snapname" 
    done
        read -p "Continue (y/n) " -n 1 -r
        echo 
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
        snap list --all | awk '/disabled/{print $1, $3}' |
        while read snapname revision; do
        snap remove "$snapname" --revision="$revision"
    done
    fi
