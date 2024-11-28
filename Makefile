PROG = tic_tac_toe
# PROG = fixed
# PROG = box
# PROG = container
# PROG = my_gtk_window
# PROG = start_gtk_app
# PROG = start

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

${PROG}: ${PROG}.c
		${CC} ${CFLAGS} -o ${PROG} ${PROG}.c ${LIBS}

clean:
		rm ${PROG}