<?php
$file = fopen("kek_all_results.txt","r");
$zazfile = fopen("zaz_all_results.txt","r");

	$scriptList = [];
	/*
	** This script runs our corewar and makes a diff with the real corewar.
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
								loadScript($file_parts['filename'], './resources_kc/' . $entry . '/' . $file_parts['filename']);
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
				if ($count2 > $count1 && $count2 < 32)
				{
					$count3 = 0;
					foreach ($scriptList as $ch3 => $path3)
					{
						if ($count3 > $count2 && $count3 < 32)
						{
							$count4 = 0;
							foreach ($scriptList as $ch4 => $path4)
							{
								if ($count4 > $count3 && $count4 < 32)
								{
									$zazStr = fgets($zazfile);
									$strFromFile = fgets($file);
									if (!$strFromFile)
									{
										$str = shell_exec('./corewar ' . $path1 . ' ' . $path2 . ' ' . $path3 . ' ' . $path4);
										$re = '/, ".*", has won !/';
										preg_match_all($re, $str, $matches, PREG_SET_ORDER, 0);
										$kek_winner = explode("\"", $matches[0][0])[1];
										file_put_contents("kek_all_results.txt", "$ch1,$ch2,$ch3,$ch4|$kek_winner\n", FILE_APPEND);
										$strFromFile = "$ch1,$ch2,$ch3,$ch4|$kek_winner\n";
									}
									if ($zazStr != $strFromFile)
									{
										echo "\033[31m[KO]\033[0m\n";
									}
									else {
										echo "\033[32m[OK]\033[0m\n";
									}
									//
									// $str = shell_exec('./corewar ' . $path1 . ' ' . $path2 . ' ' . $path3 . ' ' . $path4);
									// $re = '/, ".*", has won !/';
									// preg_match_all($re, $str, $matches, PREG_SET_ORDER, 0);
									// $my_winner = explode("\"", $matches[0][0])[1];
									// if ($my_winner != $zaz_winner)
									// 	echo "\033[31m[KO]\033[0m";
									// else
									// 	echo "\033[32m[OK]\033[0m";

									// echo $path1 . "\n" . $path2 . "\n" . $path3 . "\n" . $path4;
									// echo "\n\n\n";
								}
								$count4++;
								// $count3 += 2;
								// $count2 += 3;
								// $count1 += 4;
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
	// var_dump(count($scriptList));

	function loadScript($filename, $fullPath)
	{
		global $scriptList;

		// shell_exec('/sgoinfre/goinfre/Games/corewar/asm ' . $filename . '.s');
		$scriptList[$filename] = $fullPath . '.cor';
	}
	// var_dump($scriptList);
fclose($file);
?>
