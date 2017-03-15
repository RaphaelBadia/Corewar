;;;;#jdfkljfdslkj;fsdkjl;dfsa;;;;#jdfkljfdslkj;fsdkjl;dfsav;;;;#jdfkljfdslkj;fsdkjl;dfsa#lkkldsfajkl;dfs;jklsdf
.name "asd"#jkdfskjsdafkjl;dsafjkl;dfsa;;;;#jdfkljfdslkj;fsdkjl;dfsa
#asdkldsflkjsdfkljsdfkljsdlkj;spreadsheets#sdklfdkjldflkj;fdklj;;;;;#jdfkljfdslkj;fsdkjl;dfsa
.comment "sisi"#jdfkljfdslkj;fsdkjl;dfsa;;;;#jdfkljfdslkj;fsdkjl;dfsa
;;;;#jdfkljfdslkj;fsdkjl;dfsa
zjmp %:live
zjmp %:live_7
live %1;;;;#jdfkljfdslkj;fsdkjl;dfsa
label:;;;;#jdfkljfdslkj;fsdkjl;dfsa
live:;;;;#jdfkljfdslkj;fsdkjl;dfsa
	live %:live;;;;#jdfkljfdslkj;fsdkjl;dfsa%:live
	live %:label
	live_2:
	live_3:
	live_4:
	live_6:
	live_7:
ld %:live_7, r2
zjmp %:live_7
gg:
	ld %0, r1
	live %:gg
	live %:live_7
	live_4:
	live_6:
	live_7:
	sti r1, 20, %:gg
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	ld %0, r1
	live %:gg
	live %:live_7
	zjmp:
	zjmp %:zjmp
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	lldi %:gg, %0, r1
	sub r16, r1, r16
	ldi %:gg, %2147483648, r1
	ldi %:gg, %999999999999, r1
	; live %-4245545454454214874887884644646465431312324867864653212453
	ldi %:gg, %-999999999999, r1
	ldi %:gg, %-999999999999, r1
	ldi %:gg, %-999999999999, r1
	st r1, 65465231
