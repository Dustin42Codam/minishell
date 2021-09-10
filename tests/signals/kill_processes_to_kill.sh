kill -2 $(pidof cat)
sleep 3
kill -2 $(pidof cat)
sleep 3

kill -3 $(pidof cat)
sleep 3
kill -3 $(pidof cat)
rm minishell
echo "TAHTS IT"
