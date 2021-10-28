fd = open("smash_stack", "x")
index = 100000
fd.write("ls | ")
x = 1
while (index):
    fd.write("ls | ")
    index = index - 1
    x = x + 1
fd.write("ls ")
