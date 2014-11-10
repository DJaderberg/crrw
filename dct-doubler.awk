#!/usr/local/bin/awk -f
BEGIN {}
	{print $1, $2, "\n"$2, $1}
END {}
