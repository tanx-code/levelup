#!/bin/sh
# graphviz's can't resolve the input file with bom, but
# in Windows environment , the program always generate bom header
# when the file created , so we have to remove the header manually.
# After that , we invoke dot.exe to generate all the graph.

grep -rIlo $'^\xEF\xBB\xBF' *.gv | xargs sed --in-place -e 's/\xef\xbb\xbf//' 
mkdir DotGraph
filelist=`echo *.gv`
for file in $filelist
    do
       `dot $file -Tpng -o "DotGraph/"${file}".png"`
       done
       
