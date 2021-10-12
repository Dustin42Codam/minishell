import random
import time
import os

str_l = "qwertyuiopasdfghjklzxcvbnm"
str_u = "QWERTYUIOPASDFGHJKLZXCVBNM"
dig = "1234567890"
spec = "!@#$%^&*()_+}{\":>?<,./;`~]["


str_len = len(str_l) - 1
dig_len = len(dig) - 1
spec_len = len(spec) - 1

fout = open('fuZZ.in', "a")


def gen_chunk(time_start, time_finish, time_to_gen):
	""" chars -> \' are removed from the generation for simplicity reasons"""
	chunk = ""
	while (time_finish - time_start < time_to_gen):
		time_finish = time.time()
		com_1 = str_l[random.randint(0, str_len)] 
		com_2 = str_u[random.randint(0, str_len)]
		com_3 = dig[random.randint(0, dig_len)]
		com_4 = spec[random.randint(0, spec_len)]
		chunk = com_1 + com_2 + com_3 + com_4 + chunk
	return (chunk)

x = 0
line_cnt = 0
rans = 0

while (True):
	if (x == 0):
		line = input("how many lines of fuzzines u want?\n")
#		path_to_minishell = input("PATH to minishell -> example -> ../.././minishell\n")
		x = 1
		line = int(line)
	if (line == line_cnt):
		fout.close()
		os._exit(1)
	time_start = time.time()
	time_finish = time.time()
	time_to_gen = random.uniform(0, random.uniform(0.00001, random.uniform(0.0001, 0.01)))
	chunk = gen_chunk(time_start, time_finish, time_to_gen)
	fout.write("echo " + "'" + chunk + "'" + "\n")
	line_cnt = line_cnt + 1
