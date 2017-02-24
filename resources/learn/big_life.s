.name "big life"
.comment "why live once when we can live 21 times"

		ld %0,r2	# setting the carry to 1
		st r1,106	# writting the programm id at PC + 106
		st r1,106	# ...
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106	# ...
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106
		st r1,106	# ...

live:				# live label
		live %1		# live
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
		live %1		# ...
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1		# ...
		zjmp %:live	# jump to live label
