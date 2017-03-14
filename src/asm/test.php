<?php

	/*
	** This script runs our corewar and makes a diff with the real corewar.
	*/

	if ($handle = opendir('./tests'))
	{
		while (false !== ($entry = readdir($handle)))
		{
			if ($entry != "." && $entry != "..")
			{
				if (!is_dir('./tests/' . $entry))
					echo "./tests/$entry is not a folder !\n";
				##tests
				echo "Tests for $entry...\n";
				if ($handle2 = opendir('./tests/' . $entry))
				{
					while (false !== ($entry2 = readdir($handle2)))
					{
						if ($entry2 != "." && $entry2 != "..")
						{
							test('./tests/' . $entry . '/' . $entry2);
						}
					}
					closedir($handle);
				}
			}
		}
		closedir($handle);
	}

	function test($filename)
	{
		$correct_output = shell_exec('./tests/realasm ' . $filename);
		$asm_output = shell_exec('./asm ' . $filename . ' 2>/dev/null');
		if ($correct_output != $asm_output)
			echo "\033[31m[KO]\033[0m";
		else {
			echo "\033[32m[OK]\033[0m";
		}
		echo " $filename\n";
	}
?>
