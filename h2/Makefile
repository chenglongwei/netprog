all: 82_HW2_Q1_client 82_HW2_Q1_server_tcp_fork 82_HW2_Q1_server_tcp_pthread 82_HW2_Q1_server_tcp_poll 82_HW2_Q1_server_tcp_select 82_HW2_Q2_TCPdaytimed 82_HW2_Q2_dayTimeClient

82_HW2_Q1_client: 82_HW2_Q1_client.o
	gcc -o $@ $^

82_HW2_Q1_server_tcp_fork: 82_HW2_Q1_server_tcp_fork.o
	gcc -o $@ $^

82_HW2_Q1_server_tcp_pthread: 82_HW2_Q1_server_tcp_pthread.o
	gcc -o $@ $^ -lpthread

82_HW2_Q1_server_tcp_poll: 82_HW2_Q1_server_tcp_poll.o
	gcc -o $@ $^

82_HW2_Q1_server_tcp_select: 82_HW2_Q1_server_tcp_select.o
	gcc -o $@ $^

82_HW2_Q2_TCPdaytimed: 82_HW2_Q2_TCPdaytimed.o 82_HW2_Q2_passivesock.o 82_HW2_Q2_errexit.o
	gcc -o $@ $^ -lpthread

82_HW2_Q2_dayTimeClient: 82_HW2_Q2_dayTimeClient.o
	gcc -o $@ $^

%.o : %.c
	gcc -c -g -o $@ $< -lpthread

clean :
	rm -f *.o 82_HW2_Q1_client 82_HW2_Q1_server_tcp_fork 82_HW2_Q1_server_tcp_pthread 82_HW2_Q1_server_tcp_poll 82_HW2_Q1_server_tcp_select 82_HW2_Q2_TCPdaytimed 82_HW2_Q2_dayTimeClient


