.name "Ash"
.comment "A case to end all cases."

prep:
sti r1, %:live, %1
sti r1, %:loop, %1
sti r1, %:carry, %1
ld %9, r8
st r8, -200
ld %10, r7
ld %1, r3
ld %10, r5

loop:
live %1
fork %:carry
sub r7, r3, r7
zjmp %:carry
ld %0, r16
zjmp %:loop

carry:
live %1
xor r7, r5, r16
zjmp %:agent
ld %0, r16

live:
live %1
zjmp %:live

agent:
ldi %7, %:agent, r2
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
live %1
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
st r2, 256
live %1
