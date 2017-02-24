.name "pussy_destroyer"
.comment "is that name correct?"

entry:
		sti r1,%:live,%1
		sti r1,%:live_attack1,%1
		sti r1,%:live_attack2,%1
		sti r1,%:flive1,%1
		sti r1,%:flive2,%1
		sti r1,%:flive3,%1
		sti r1,%:wall,%1
		ld %0,r16
flive1:
		live %1
		fork %:big_live_init
		ld %1111638594,r2
		ld %0,r16
flive2:
		live %1
		fork %:live
flive3:
		live %1
		fork %:wall
		zjmp %:attack_init

wall:
		live %1
		st r2, -24
		st r2, -33
		st r2, -42
		st r2, -76
		st r2, -60
		st r2, -69
		st r2, -78
		st r2, -87
		st r2, -96
		st r2, -105
		st r2, -114
		st r2, -123
		st r2, -132
		st r2, -141
		st r2, -150
		st r2, -159
		st r2, -168
		st r2, -177
		st r2, -186
		st r2, -195
		st r2, -204
		st r2, -213
		st r2, -222
		st r2, -231
		st r2, -240
		st r2, -249
		st r2, -258
		st r2, -267
		st r2, -276
		st r2, -285
		st r2, -294
		st r2, -303
		st r2, -312
		st r2, -321
		st r2, -330
		st r2, -339
		st r2, -348
		st r2, -357
		st r2, -366
		st r2, -376
		st r2, -384
		st r2, -393
		st r2, -402
		st r2, -411
		st r2, -420
		st r2, -429
		st r2, -438
		st r2, -447
		st r2, -456
		st r2, -465
		st r2, -474
		st r2, -483
		st r2, -492
		st r2, -501
		st r2, -760
		zjmp %:wall

big_live_init:
		ld %0,r2
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76
		st r1,76

big_live:
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		zjmp %:big_live

live:
		live %1
		zjmp %:live

attack_init:
		ld %5,r2
		ld %1,r3
		ld %4,r4
		ld %0,r5
		ld %300,r7

attack:
		ld %0,r16
live_attack1:
		live %1
		add r2,r3,r2
		ldi %:attack_init,r5,r6
		sti r6,%:live,r7
live_attack2:
		live %1
		add r5,r4,r5
		add r7,r4,r7
		xor %31,r2,r16
		zjmp %:endwhile
		ld %0,r16
		zjmp %:attack
endwhile:
		zjmp %118
