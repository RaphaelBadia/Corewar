<?php

	/*
	** This script runs our asm and makes a diff with the real asm.
	*/

	if ($handle = opendir('./resources_kc'))
	{
		while (false !== ($entry = readdir($handle)))
		{
			if ($entry != "." && $entry != "..")
			{
				if (!is_dir('./resources_kc/' . $entry))
					echo "./resources_kc/$entry is not a folder !\n";
				##tests
				// echo "Tests for $entry...\n";
				if ($handle2 = opendir('./resources_kc/' . $entry))
				{
					while (false !== ($entry2 = readdir($handle2)))
					{
						if ($entry2 != "." && $entry2 != "..")
						{
							$file_parts = pathinfo($entry2);
							if ($file_parts['extension'] == "s")
							{
								test('/Users/rbadia/Desktop/corewar/resources_kc/' . $entry . '/' . $file_parts['filename']);
							}
						}
					}
					closedir($handle2);
				}
			}
		}
		closedir($handle);
	}

	function test($filename)
	{
		// echo $filename . ".s\n";
		shell_exec('/sgoinfre/goinfre/Games/corewar/asm ' . $filename . '.s');
		shell_exec("mv $filename.cor $filename.correal");
		shell_exec('./src/asm/asm ' . $filename . '.s');
		shell_exec('hexdump ' . $filename . '.correal > ' . $filename . '.zaz_hexdump');
		shell_exec('hexdump ' . $filename . '.cor > ' . $filename . '.our_hexdump');
		$correct_output = shell_exec('diff ' . $filename . '.our_hexdump ' . $filename . '.zaz_hexdump');
		if ($correct_output != "")
			echo "\033[31m[KO]\033[0m";
		else
			echo "\033[32m[OK]\033[0m";
		echo " $filename\n";
	}
?>
