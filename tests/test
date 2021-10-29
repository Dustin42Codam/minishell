file_name="1 2 3 4 5 6 7 8 9 10"
echo "Give the amount of comands u want to tets"
index=0
x=0
exit_status=0
read index
echo "Testing $index comand's"
while [ $index -gt 0 ]
do
	x=$((1 + RANDOM % 10))
	echo $x
	# bash -c "cat ${file_name[$x]}"
	exit_status=$?
	((index=index-1))
	echo Number $index
done