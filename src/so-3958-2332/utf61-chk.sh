# Generate files for UTF16/ITF32 BOM checking

genchar -nx FF FE 00 00 > utf-32LE
genchar -nx 00 00 FE FF > utf-32BE
genchar -nx FF FE 30 00 > utf-16LE
genchar -nx FE FF 00 30 > utf-16BE
genchar -nx FE FF       > utf-16BE.2
genchar -nx FF FE       > utf-16LE.2

for file in utf-*
do
    ls -l $file
    odx $file | sed 2d
    printf 'File: %-12s - content: %s\n' $file $(utf61 $file)
done
