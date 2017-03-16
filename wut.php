<?php

	$name = 'and';
	$regPossibilities = array(
		'r1',
		'r2',
		'r7',
		'r16'
	);
	$dirPossibilities = array(
		"%-2147483648",
		"%2147483648",
		"%2147483647",
		"%214748364732488",
		"%1",
		"%-1",
		"%10",
		"%-10",
		"%-500",
		"%500",
		"%:before",
		"%:middle",
		"%:after"
	);
	$indPossibilities = array(
		"-2147483648",
		"2147483648",
		"2147483647",
		"214748364732488",
		"1",
		"-1",
		"10",
		"-10",
		"-500",
		"500",
		":before",
		":middle",
		":after"
	);
	// T_REG | T_DIR | T_IND,          T_REG | T_DIR | T_IND,      T_REG

	echo ".name \"$name\"\n.comment \"lol\"\n\nbefore:\nbefore:\n";
	function display($p1, $p2, $p3)
	{
		global $name;

		echo "$name $p1, $p2, $p3\n";
	}

	foreach ($regPossibilities as $p3)
	{
		echo "\nmiddle:\n";
		foreach ($dirPossibilities as $p2)
		{
			foreach ($dirPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
			foreach ($indPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
			foreach ($regPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
		}
		foreach ($indPossibilities as $p2)
		{
			foreach ($dirPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
			foreach ($indPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
			foreach ($regPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
		}
		foreach ($regPossibilities as $p2)
		{
			foreach ($dirPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
			foreach ($indPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
			foreach ($regPossibilities as $p1)
			{
				display($p1, $p2, $p3);
			}
		}
		echo "\nafter:\n";
	}
?>
