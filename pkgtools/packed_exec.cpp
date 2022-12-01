#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <zlib.h>
#include <limits.h>
#include <chrono>
#include <thread>

extern "C" char _binary_publish_bar_gz_start[];
extern "C" char _binary_publish_bar_gz_end[];

int getname(char *name, gzFile fp )
{
	while(1)
	{
		int c = gzgetc(fp);
		if( c == ' ' || c == '\n' || c < 0 )
		{
			*name = 0;
			return c;
		}
		*(name++) = c;
	}
}

void exbargz(char *filename )
{
	gzFile fp = gzopen(filename, "rb" );
	if( !fp )
		return;
	while(!gzeof(fp))
	{
		char name[4096];
		//yes, it's unsafe, so what?
		int c = getname(name, fp );
		if( c < 0 )
			break;
		else if( c == '\n' )
		{
			//printf("extracting dirname: %s\n", name );
			mkdir(name, 0755 );
		}
		else
		{
			unsigned int fsize;
			gzread(fp, &fsize, sizeof(unsigned int) );
			//printf("extracting filename: %s\tsize: %u\n", name, fsize );
			char *buf = (char *)malloc(fsize);
			gzread(fp, buf, fsize );
			FILE *ofp = fopen(name, "wb" );
			if( ofp != NULL )
			{
				fwrite(buf, 1, fsize, ofp );
				fclose(ofp);
			}
			free(buf);
			chmod(name, 0700 );
		}
	}
}

int main(int argc, char **argv )
{
	char cwd[PATH_MAX];
	struct stat sb;
	std::string appdata = "/tmp/FastVideoDS/";
	if(stat(appdata.c_str(), &sb) != 0)
	{
		getcwd(cwd, sizeof(cwd) );
		mkdir(appdata.c_str(), 0755 );
		chdir(appdata.c_str());
		std::ofstream("FastVideoDS.bar.gz", std::ofstream::binary | std::ofstream::trunc ).write(_binary_publish_bar_gz_start, _binary_publish_bar_gz_end - _binary_publish_bar_gz_start );
		exbargz((char *)"FastVideoDS.bar.gz");
		chdir(cwd);
		execv("/tmp/FastVideoDS/publish/FastVideoDSEncoder", argv );
	}
	else if( S_ISDIR(sb.st_mode) )
		execv("/tmp/FastVideoDS/publish/FastVideoDSEncoder", argv );
	std::cerr << "Error executing /tmp/FastVideoDS/publish/FastVideoDSEncoder consider checking and deleting /tmp/FastVideoDSEncoder" << std::endl;
	return 1;
}
