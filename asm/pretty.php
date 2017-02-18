#!/usr/bin/php
<?php

	/*
	** This file makes the hexdump -v command pretty
	** It prints in PINK the magic Number
	** In Green the name of the program
	** In Red the size of the champion
	** In Yellow the comment

	./tests/realasm ./play.s && hexdump -v ./play.cor | php pretty.php
	*/

	$magic = 4;
	$pname = $magic + 129 + 3; // THERE IS A PADDING OF 3
	$psize = $pname + 4;
	$comment = $psize + 2049;
	$i = 0;
	$show_star = false;
	while($line = fgets(STDIN))
	{
		$bytestring = substr($line, 8);
		if ($bytestring == "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n")
		{
			$show_star = true;
			$i += 16;
		}
		else
		{
			if ($show_star)
			{
				echo "*\n";
				$show_star = false;
			}
			$beginning = substr($line, 0, 8);
			$bytes = explode(' ', $bytestring);
			foreach ($bytes as $value)
			{
				if ($i >= 0)
					echo "\033[38;5;213m";
				if ($i >= $magic)
					echo "\033[38;5;22m";
				if ($i >= $pname)
					echo "\033[31m";
				if ($i >= $psize)
					echo "\033[38;5;58m";
				if ($i >= $comment)
					echo "\033[0m";
				echo " ";
				echo $value;
				$i++;
			}
		}
	}
?>
