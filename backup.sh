#!/bin/bash
# 把git仓库变成普通仓库。同时保留git记录。
for dir in ./*; do
    if [ -d "$dir" ]; then
        cd $dir
        mv .git .backup_git
        cd -
    fi
done

