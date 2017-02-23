.comment "just a basic living prog"
.name      "civn"

 l2:	sti r1, %:label, %1
		and r1,%0,r1
label:
		live         %1
		zjmp  %:label
