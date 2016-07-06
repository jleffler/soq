tmpdir=$(mktemp -d ./rename.XXXXXX)
trap "rm -fr $tmpdir; exit 1" 0 1 2 3 13 15

(
cd $tmpdir || exit 1
counter=0

for file1 in file.1 file.2 link.1 link.2
do
    for file2 in file.1 file.2 link.1 link.2
    do
        boxecho $((counter++)): $file1 $file2
        rm -f *
        echo file 1 > file.1
        echo file 2 > file.2
        ln -s file.1 link.1
        ln -s file.2 link.2
        ls -li
        ../test-rename $file1 $file2
        ls -li
    done
done
)

rm -fr $tmpdir
trap 0
