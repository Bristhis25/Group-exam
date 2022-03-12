#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int add_pipe (void);
int add_fifo (void);

int main (void)
{
	if ((add_pipe ()) == 0)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

int add_pipe (void)
{
	// rem : le tube est limit� aux nombres de descendants du processus !
	int tube[2];
	int buffer1[2];
	int buffer2[1];

	if (pipe (tube) != 0)	// cr�ation du tube
	{
		perror ("pipe");
		return -1;
	}
	switch (fork ())
	{
	case -1:
		perror ("fork()");
		return -1;
		break;
	case 0:
		// pocessus fils
		if (read (tube[0], buffer1, 2 * sizeof (int)) !=
		    2 * sizeof (int)) // lecture des donn�es envoy�es par le p�re
		{
			perror ("[Fils] read");
			return -1;
		}
		fprintf (stdout,
			 "[Fils] Lecture des valeurs %d\n",
			 buffer1[0], buffer1[1]);
		close (tube[0]); // fermeture du pipe en lecture
		if (write (tube[1], buffer2, sizeof (int)) != sizeof (int))
		// �criture de la r�ponse dans le pipe
		{
			perror ("[Fils] write");
			return -1;
		}
		close (tube[1]); // fermeture du pipe en �criture
		break;
	default:
		// processus p�re
		buffer1[0] = 2;
		buffer1[1] = -57;
		if (write (tube[1], buffer1, 2 * sizeof (int)) !=
		    2 * sizeof (int)) // �criture des donn�es dans le pipe
		{
			perror ("[P�re] write");
			return -1;
		}
		fprintf (stdout,
			 "[P�re] Envoi des valeurs %d et %d\n",
			 buffer1[0], buffer1[1]);
		close (tube[1]); /// Fermeture du pipe
		wait (NULL); // attente de la fin du processus fils
		if (read (tube[0], buffer2, sizeof (int)) != sizeof (int))
		// lecture du r�sultat dans le pipe
		{
			perror ("[P�re] read");
			return -1;
		}
		close (tube[0]); // fermeture du pipe en lecture
		fprintf (stdout, "[P�re] Lecture du r�sultat : %d\n",
			 buffer2[0]);
		break;
	}
	return 0;
}
