

main:
	gcc -g main.c prompt.c warp.c peek.c others.c proclore.c pastevents.c seek.c utilities.c iman.c ping.c execution.c neonate.c pipes.c activity.c fg_bg.c inp_redir.c sighandle.c

main_test:
	gcc -g main_test.c prompt.c warp.c peek.c others.c proclore.c pastevents.c seek.c utilities.c iman.c 