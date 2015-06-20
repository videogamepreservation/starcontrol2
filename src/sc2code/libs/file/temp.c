/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

// Contains code handling temporary files and dirs

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include <errno.h>

#include "filintrn.h"

static char *tempDir;

void
removeTempDir (void) {
	rmdir(tempDir);
}

void
initTempDir (void) {
	size_t len;

	tempDir = malloc(L_tmpnam);
	if (tmpnam(tempDir) == NULL) {
		fprintf(stderr, "Fatal error: Cannot get a name for a temporary "
				"directory.\n");
		exit(EXIT_FAILURE);
	}

	len = strlen(tempDir);
	if (len > MAXPATHLEN - 13) {
		// reserve space for a filename of at least 12 characters
		fprintf(stderr, "Fatal error: Path to temp dir too long.\n");
		exit(EXIT_FAILURE);
	}
	if (mkdir(tempDir, 0700) == -1) {
		fprintf(stderr, "Fatal error: Cannot create a temporary "
				"directory: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	tempDir = realloc(tempDir, len);
	atexit(removeTempDir);
}

void
unInitTempDir (void) {
	// nothing at the moment.
	// the removing of the dir is handled via atexit
}

// return the path to a file in the temp dir with the specified filename.
// returns a pointer to a static buffer.
char *
tempFilePath (const char *filename) {
	static char file[MAXPATHLEN];
	
	if (snprintf(file, MAXPATHLEN, "%s/%s", tempDir, filename) == -1) {
		fprintf(stderr, "Path to temp file too long.\n");
		exit(EXIT_FAILURE);
	}
	return file;
}

