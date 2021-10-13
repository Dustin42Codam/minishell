a = 10000 
x = ""
x_2 = ""
s_2 = "\" "
s = "./minishell -c \" "
f = open("guru99.txt","w+")
while (a != 0):
	x = x + s
	x_2 = x_2 + s_2
	a = a - 1
f.write(x + x_2) 
