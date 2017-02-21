.name "basic"
.comment "You're my soon"

		sti r1,%:live,%1	# writing the program id after live label
		ld r1,%0			# setting the carry to 1 for zjump

live:						# live label
		live %1				# live
		zjmp %:live			# jump to live label
