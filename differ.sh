#!/bin/zsh
i=$1;
# gcc *.c -lncurses -lcurses
args="./resources_kc/lseguin/skynet.cor ./resources_kc/sbuono/Asombra.cor ./resources_kc/hmoutaou/Misaka_Mikoto.cor ./resources_kc/gbir/_.cor"
while test $i != $2
do
	# la commande "touch" permet de créer un fichier vide :
	#touch fichier"$i"
	printf "Cycle $i ..."
	#./a.out -dump $i ./resources_kc/lseguin/skynet.cor | egrep 0x > results/us
	#/sgoinfre/goinfre/Games/corewar/corewar -d $i ./resources_kc/lseguin/skynet.cor | egrep 0x > results/zaz
	DIFF="$(diff <(./a.out -dump $i ./resources_kc/gbir/_.cor | egrep 0x) <(/sgoinfre/goinfre/Games/corewar/corewar -d $i ./resources_kc/gbir/_.cor | egrep 0x))"
	if [ "$DIFF" != "" ]
	then
		diff <(./a.out -dump $i ./resources_kc/gbir/_.cor | egrep 0x) <(/sgoinfre/goinfre/Games/corewar/corewar -d $i ./resources_kc/gbir/_.cor | egrep 0x)
		break;
	else
		printf "diff ok\n"
	fi
	i=$(($i + 1))
done
