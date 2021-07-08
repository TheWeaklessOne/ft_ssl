#!/bin/bash

#
#	PREPARE
#

MY=""
ORIGINAL=""

function compare_strings {
	printf "%s" "testing $1, $2: "
    if [ "$MY" == "$ORIGINAL" ]
		then
			printf "%s\n" "results are equal"
		else
			printf "%s\n%s\n%s\n" "results are not equal:" "$MY" "$ORIGINAL"
	fi
}

function test {
	MY=$(../ft_ssl "$1" "$2" | awk 'END {print $NF}')
	ORIGINAL=$(openssl "$1" "$2" | awk 'END {print $NF}')

	compare_strings "$1" "$2"
}

#
#	TESTS
#

make -C ..

echo

# MD5
test md5 empty.txt
test md5 long.txt
echo

# SHA256
test sha256 empty.txt
test sha256 long.txt
echo