#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int isDirectory(const char *path)
{
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
}

int main(int argc, char **argv )
{
	if( argc < 2 )
		return 1;
	FILE *fp = fopen(argv[1], "wb" );
	if( fp == NULL )
		return 1;
	char name[2048];
	while( !feof(stdin) && scanf("%2047[^\n]%*c", name ) )
	{
		if( isDirectory(name) )
		{
			fprintf(fp, "%s\n", name );
		}
		else
		{
			FILE *ifp = fopen(name, "rb" );
			if( ifp != NULL )
			{
				fprintf(fp, "%s ", name );
				unsigned int fsize = (fseek(ifp, 0, SEEK_END ), ftell(ifp) ); fseek(ifp, 0, SEEK_SET );
				fwrite(&fsize, sizeof(unsigned int), 1, fp );
				char *buf = malloc(fsize);
				fread(buf, 1, fsize, ifp );
				fwrite(buf, 1, fsize, fp );
				fclose(ifp);
				free(buf);
			}
		}
	}
	fclose(fp);
}
