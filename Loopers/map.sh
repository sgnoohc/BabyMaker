for ITEM in $(ls $1/*out); do
    echo $(grep 'Looping \|TRANSFER:EXIT\|cp' $ITEM | tr '\n' ' ');
done | awk 'function basename(file, a, n) { n = split(file, a, "/"); return a[n]; } function basename2(file, a, n) { n = split(file, a, ".root"); return a[1]; } {print basename2($4)".root", basename($12)}'
