.name "test"
.comment "OUKT"

ld %15, r2
ld %15, r3
live:
st r1, 6
live %1
sti r2, r3, r77
zjmp %:live
fork %233
