/^		/ {
    s///
    w file.3
    d
}
/^	/ {
    s///
    w file.2
    d
}
/^[^	]/ {
    w file.1
    d
}
