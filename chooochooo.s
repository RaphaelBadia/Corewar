	.name "TCHOOTCHOO"
	.comment "motherkeker of asd"

android:
	ld %0, r16
	sti r1, %:humanity, %1
humanity:
	live %724249387
	zjmp %:virus
virus:
	fork %:malware
	live %724249387
	fork %:android
	fork %:oschip_base
	ld %0, r16
	zjmp %:programpodshield
malware:
	fork %:worm
	fork %:oschip_hud
	ld %0, r16
	zjmp %:programpodshield
worm:
	fork %:oschip_control
programpodshield:
	ld %0, r16
	sti r1, %10, %0
	live %724249387
	zjmp %:programpodshield
oschip_base:
	ld %190058248, r15
	ld %10, r8
	ld %0, r16
	sti r15, %:machine, %0
	zjmp %:machine
oschip_hud:
	ld %151071531, r15
	ld %14, r8
	ld %0, r16
	sti r15, %:machine, %4
	zjmp %:machine
oschip_control:
	ld %724238336, r15
	ld %18, r8
	ld %0, r16
	sti r15, %:machine, %8
	zjmp %:machine
machine:
	aff r2
