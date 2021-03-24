/*
* wytar.c
* Charles Myers
* COSC 3750 Spring 2021
* Homework 6
* March 23, 2021
*
* This file is our version of tar
*/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<errno.h>
#include<tar.h>
#include<grp.h>
#include<pwd.h>
#include"tar_header.h"
int main(int argc, char* argv[]) {
	int cflag = 0, xflag = 0, fflag = 0, arcflag = 0, filecount = 0;
	string archiveName;
	string filenames[argc];
	struct tar_struct archive = NULL;
	if(argc < 4) {
		printf("Invalid Number of Arguments \n");
		return -1;
	}
	for(int i = 1; i < argc;i++) {
		if(strcmp(argv[i], "-c") && i < 4) {
			cflag = 1;	
		}
		else if(strcmp(argv[i], "-cf") || strcmp(argv[i], "-fc" && i < 4)) {
			cflag = 1;
			fflag = 1;
		}
		else if (strcmp(argv[i], "-x") && xflag == 0) {
			xflag = 1;
		}
		else if(strcmp(argv[i], "-xf") || strcmp(argv[i], "-fx") && i < 4) {
			xflag = 1;
			fflag = 1;
		}
		else if((strcmp(argv[i], "-f") {
			fflag = 1;
		}
		else if(arcflag == 0) {
			archiveName = argv[i];
			arcflag = 1;
		}
		else {
			filenames[filecount] = argv[i];
			filecount++;
		}
	}
	if(cflag == 1 && xflag == 1) {
		printf("Invalid Options \n");
	}
	else if(fflag == 0 || arcflag == 0) {
		printf("Invalid Options \n");
	}
	else if(filenames[0].length == 0 && cflag == 1) {
		printf("Invalid Options \n");
	}
	//Start of write
	else if(cflag == 1) {
		int *infile;
		infile = fopen(archiveName, "r");
		struct stat stats;
		char buffer[512];
		if(infile == NULL) {
			printf("Cannot create or open archive \n");
			return -1;
		}
		fclose(infile);
		for(int i = 0; i < filecount; i++) {
			if(lstat(filenames[i],&stats) != 0) {
				printf("Cannot stat \n");
				//return -1;
			}
			//Create the header
			strncpy(archive.name, filenames[i],100);
			strcat(buffer,archive.name);
			snprintf(archive.mode,8,"%07o", stats.st_mode & S_IRWXU, );
			strcat(buffer,archive.mode);
			snprintf(archive.uid,8,"%07o", stats.st_uid);
			strcat(buffer,archive.uid);
			snprintf(archive.gid,8,"%07o", stats.st_gid);
			strcat(buffer,archive.gid);
			snprintf(archive.size, 12,"%011o",(int) stats.st_size);
			strcat(buffer,archive.size);
			snprintf(archive.mtime, 12, "%011o", (int) stats.mtime);
			strcat(buffer,archive.mtime);
			snprintf(archive.devmajor, 8, "%07o", 0);
			strcat(buffer,archive.devmajor);
			snprintf(archive.devminor, 8, "%07o", 0);
			strcat(buffer,archive.devminor);
			snprintf(archive.magic, 6, "%06o", "TMAGIC");
			strcat(buffer,archive.magic);
			snprintf(archive.version, 2, "%01o", 0);
			strcat(buffer,archive.version);
			if(stats.st_mode & S_IFMT) == S_IFREG) {
				archive.typeflag = REGTYPE;
				strcat(buffer,archive.typeflag);
			}
			else if(stats.st_mode & S_IFMT) == S_IFDIR) {
				archive.typeflag = DIRTYPE;
				snprintf(archive.size, 12,"%011o",0);
				strcat(buffer,archive.typeflag);
				strcat(buffer,archive.size);
			}
			else if(stats.st_mode & S_IFMT) == S_IFLNK) {
				archive.typeflag = SYMTYPE;
				snprintf(archive.size, 12,"%011o",0);
				readlink(filenames[i], archive.linkname,100);
				strcat(buffer,archive.typeflag);
				strcat(buffer,archive.size);
				strcat(buffer,archive.linkname);
			}
			struct passwd *pwd;
			struct group *grp;
			
			pwd = getpwuid(stats.st_uid);
			
			grp = getgrgid(stats.st_gid);
			strncpy(archive.uname, pwd->pw_name,32);
			strcat(buffer,archive.uname);
			strncpy(archive.gname, grp->gr_name,32);
			strcat(buffer,archive.gname);
			strncpy(archive.prefix, 0,155);
			strcat(buffer,archive.prefix);
			snprintf(archive.pad, 12, "%012o", 0);
			
			memset(archive.chksum, ' ', 8);
			unsigned int check = 0;
			for(int z = 0; z < 512; z++) {
				check += buffer[i];
			}
			snprintf(archive.chksum, 8, "%06o0", check);
			archive.chksum[6] = '\0';
			archive.chksum[7] = ' ';
			//end of header creation
			//write header
			infile = fopen(archiveName, "r");
			fwrite(&archive,1,sizeof(struct tar_struct),infile);
			fclose(infile);
			
			
		}
		
		
	}
}