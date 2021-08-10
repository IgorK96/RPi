gpio -g mode 20 out
while true
do
	gpio -g write 20 1
	sleep 1
	gpio -g write 20 0
	sleep 1
done
