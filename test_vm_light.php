<?php
	$scriptList = [];
	/*
	** This script runs our corewar and makes a diff with the real corewar.
	** Takes 1hour max to run.
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
								loadScript($file_parts['filename'], '/Users/rbadia/Desktop/corewar/resources_kc/' . $entry . '/' . $file_parts['filename']);
							}
						}
					}
					closedir($handle2);
				}
			}
		}
		closedir($handle);
	}
	$count1 = 0;
	foreach ($scriptList as $ch1 => $path1)
	{
		if ($count1 >= 0 && $count1 < 29)
		{
			$count2 = 0;
			foreach ($scriptList as $ch2 => $path2)
			{
				if ($count2 == $count1 + 1 && $count2 < 30)
				{
					$count3 = 0;
					foreach ($scriptList as $ch3 => $path3)
					{
						if ($count3 == $count2 + 1 && $count3 < 31)
						{
							$count4 = 0;
							foreach ($scriptList as $ch4 => $path4)
							{
								if ($count4 == $count3 + 1 && $count4 < 32)
								{
									$str = shell_exec('/sgoinfre/goinfre/Games/corewar/corewar ' . $path1 . ' ' . $path2 . ' ' . $path3 . ' ' . $path4);
									$re = '/, ".*", has won !/';
									preg_match_all($re, $str, $matches, PREG_SET_ORDER, 0);
									$zaz_winner = explode("\"", $matches[0][0])[1];

									$str = shell_exec('./corewar ' . $path1 . ' ' . $path2 . ' ' . $path3 . ' ' . $path4);
									$re = '/, ".*", has won !/';
									preg_match_all($re, $str, $matches, PREG_SET_ORDER, 0);
									$my_winner = explode("\"", $matches[0][0])[1];
									if ($my_winner != $zaz_winner)
										echo "\033[31m[KO]\033[0m";
									else
										echo "\033[32m[OK]\033[0m";
										echo "$ch1 vs $ch2 vs $ch3 vs $ch4\n";
								}
								$count4++;
							}
						}
						$count3++;
					}
				}
				$count2++;
			}
		}
		$count1++;
	}

	function loadScript($filename, $fullPath)
	{
		global $scriptList;

		shell_exec('/sgoinfre/goinfre/Games/corewar/asm ' . $filename . '.s');
		$scriptList[$filename] = $fullPath . '.cor';
	}
?>
