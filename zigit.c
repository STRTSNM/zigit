#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int download(const char *url) {
	char cmd[512];
	snprintf(cmd, sizeof(cmd), "aria2c %s", url);
	return system(cmd); //the result of the execution --> 0 for success
}

char* pstr(const char *branch, const char *url) {
	const char *sfx = "/zip/";
	const char *pfx1 = "https://github.com/";
	const char *pfx2 = "https://codeload.github.com/";

	size_t len = strlen(pfx2) + strlen(url + strlen(pfx1)) + strlen(sfx) + strlen(branch) + 1;
	char *nurl = malloc(len);
	if (!nurl) return NULL;

	nurl[0] = '\0';
	strcat(nurl, pfx2);
	strcat(nurl, url + strlen(pfx1));
	strcat(nurl, sfx);
	strcat(nurl, branch);

	return nurl;
}

int unzip(const char *branch, const char *name) {
	char zipname[512];
	snprintf(zipname, sizeof(zipname), "%s-%s.zip", name, branch);
	printf("\nZip name is %s\n", zipname);

	char cmd[512];
	snprintf(cmd, sizeof(cmd), "unzip -q %s", zipname);
	int r = system(cmd);

	char cmd1[512];
	snprintf(cmd1, sizeof(cmd1), "mv %s-%s %s", name, branch, name);
	system(cmd1);

	remove(zipname);
	return r;
}

int main(int argc, char *argv[]) {
	if (argc < 3 || strcmp(argv[1], "clone") != 0) {
		fprintf(stderr, "Usage: %s clone <github_repo_url> [-b branch]\n", argv[0]);
		return 1;
	}

	const char *url = argv[2];
	const char *name = strrchr(url, '/') + 1;
	const char *branch = NULL;

	// Parse branch argument
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--branch") == 0) {
			if (i + 1 < argc)
				branch = argv[i + 1];
		}
	}

	printf("\nBranch is : %s\n", branch ? branch : "(none)");

	if (!branch) {
		char *download_url = pstr("main", url);
		printf("Downloading from: %s\n", download_url);
		int r1 = download(download_url);
		free(download_url);

		if (r1 != 0) {
			printf("main branch not found. Trying master...\n");
			download_url = pstr("master", url);
			int r2 = download(download_url);
			free(download_url);
			if (r2 != 0) {
				fprintf(stderr, "Error: Could not download repository.\n");
				return 1;
			}
			unzip("master", name);
		} else {
			unzip("main", name);
		}
	} else {
		// Custom branch
		char *download_url = pstr(branch, url);
		printf("Downloading from: %s\n", download_url);
		int r = download(download_url);
		if (r == 0)
			unzip(branch, name);
		else
			fprintf(stderr, "Error: Could not download branch %s.\n", branch);
		free(download_url);
	}

	printf("Done!\n");
	return 0;
}
