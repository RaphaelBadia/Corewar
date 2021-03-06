<?php

	/*
	** This script runs our corewar and makes a diff with the real corewar.
	*/

	if ($handle2 = opendir('./tests/'))
	{
		while (false !== ($entry2 = readdir($handle2)))
		{
			if ($entry2 != "." && $entry2 != "..")
			{
				$file_parts = pathinfo($entry2);
				if ($file_parts['extension'] == "s")
				{
					test('./tests/' . $file_parts['filename']);
				}
			}
		}
		closedir($handle2);
	}

	function test($filename)
	{
		// echo $filename . ".s\n";
		shell_exec('/sgoinfre/goinfre/Games/corewar/asm ' . $filename . '.s');
		shell_exec("mv $filename.cor $filename.correal");
		shell_exec('./asm ' . $filename . '.s');
		shell_exec('hexdump ' . $filename . '.correal > ' . $filename . '.zaz_hexdump');
		shell_exec('hexdump ' . $filename . '.cor > ' . $filename . '.our_hexdump');
		$correct_output = shell_exec('diff ' . $filename . '.our_hexdump ' . $filename . '.zaz_hexdump');
		if ($correct_output != "")
			echo "\033[31m[KO]\033[0m";
		else
			echo "\033[32m[OK]\033[0m";
		echo " $filename.s\n";
	}
?>
