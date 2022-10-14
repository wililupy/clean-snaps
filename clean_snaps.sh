#!/bin/bash
# Remove old revisions of snaps
# Make sure that snaps (like snap-store) are disabled
set -eu

LANG=C snap list --all | awk '/disabled/{print $1, $3}' |
    while read snapname revision; do
        snap remove "$snapname" --revision="$revision"
    done

