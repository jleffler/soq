/^\t\t/ {
    s///
    w file.3
    d
}
/^\t/ {
    s///
    w file.2
    d
}
/^[^\t]/ {
    w file.1
    d
}
