#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* pstr(int m, const char *url) {
	const char *sfx = (m == 1) ? "/zip/main" : "/zip/master";
	const char *pfx1 = "https://github.com/";
	const char *pfx2 = "https://codeload.github.com/";

	size_t len = strlen(pfx2) + strlen(url + strlen(pfx1)) + strlen(sfx) + 1;
	char *nurl = malloc(len);
	if (!nurl) return NULL;

	nurl[0] = '\0';
	strcat(nurl, pfx2);
	strcat(nurl, url + strlen(pfx1));
	strcat(nurl, sfx);

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
		fprintf(stderr, "Usage: %s clone <github_repo_url>\n", argv[0]);
		return 1;
	}

	const char *url = argv[2];
	const char *name = strrchr(url, '/') + 1;

	char *download_url = pstr(1, url);
	printf("Downloading from: %s\n", download_url);

	char cmd[512];
	snprintf(cmd, sizeof(cmd), "aria2c %s", download_url);
	int r1 = system(cmd);
	free(download_url);

	if (r1 != 0) {
		printf("main branch not found. Trying master...\n");
		download_url = pstr(2, url);
		snprintf(cmd, sizeof(cmd), "aria2c %s", download_url);
		int r2 = system(cmd);
		free(download_url);
		if (r2 != 0) {
			fprintf(stderr, "Error: Could not download repository.\n");
			return 1;
		}
		unzip("master", name);
	} else {
		unzip("main", name);
	}

	printf("Done!\n");
	return 0;
}
