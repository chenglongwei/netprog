all:  81_HW1_Q1.o 81_HW1_Q2_sum.o 81_HW1_Q2.o 81_HW1_Q4_server_tcp.o 81_HW1_Q4_client_tcp.o 81_HW1_Q4_server_udp.o 81_HW1_Q4_client_udp.o

81_HW1_Q1.o:  81_HW1_Q1.c
	gcc 81_HW1_Q1.c -o 81_HW1_Q1.o

81_HW1_Q2_sum.o:  81_HW1_Q2_sum.c
	gcc 81_HW1_Q2_sum.c -o 81_HW1_Q2_sum.o

81_HW1_Q2.o:  81_HW1_Q2.c
	gcc 81_HW1_Q2.c -o 81_HW1_Q2.o

81_HW1_Q4_server_tcp.o:	81_HW1_Q4_server_tcp.c
	gcc 81_HW1_Q4_server_tcp.c -o 81_HW1_Q4_server_tcp.o

81_HW1_Q4_client_tcp.o:	81_HW1_Q4_client_tcp.c
	gcc 81_HW1_Q4_client_tcp.c -o 81_HW1_Q4_client_tcp.o

81_HW1_Q4_server_udp.o:	81_HW1_Q4_server_udp.c
	gcc 81_HW1_Q4_server_udp.c -o 81_HW1_Q4_server_udp.o

81_HW1_Q4_client_udp.o:	81_HW1_Q4_client_udp.c
	gcc 81_HW1_Q4_client_udp.c -o 81_HW1_Q4_client_udp.o

clean:
	rm *.o
