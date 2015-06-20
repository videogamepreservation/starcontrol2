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

/*
 * Eventually this should include all configuration stuff, 
 * for now there's few options which indicate 3do/pc flavors.
 * By Mika Kolehmainen.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include "compiler.h"
#include "options.h"
#include "file.h"

int optWhichMusic = MUSIC_3DO;
char *configDir, *saveDir;
BOOLEAN optSubtitles = TRUE;

BOOLEAN FileExists (char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
        return FALSE;

    fclose (fp);
    return TRUE;
}

void
prepareConfigDir(void) {
	char *cdir;

	cdir = getHomeDir();
	if (cdir == NULL) {
		fprintf(stderr, "Fatal error: Cannot determine config dir.\n");
		exit(EXIT_FAILURE);
	}
	
	configDir = malloc(MAXPATHLEN);
	if (snprintf(configDir, MAXPATHLEN - 13, "%s/%s", cdir,
			CONFIGDIR) == -1) {
		// Doesn't have to be fatal, but might mess up things when saving
		// config files.
		fprintf(stderr, "Fatal error: Path to config files too long.\n");
		exit(EXIT_FAILURE);
	}
	
	configDir = realloc(configDir, strlen(configDir));

	// Create the path upto the config dir, if not already existing.
	mkdirhier (configDir);
}

void
prepareSaveDir(void) {
	char *home;

	home = getHomeDir();
	if (home == NULL) {
		fprintf(stderr, "Fatal error: Cannot determine home dir.\n");
		exit(EXIT_FAILURE);
	}
	
	saveDir = malloc(MAXPATHLEN);
	if (snprintf(saveDir, MAXPATHLEN - 13, "%s/%s", home, SAVEDIR) == -1) {
		// Doesn't have to be fatal, but the player wouldn't be able
		// to save, and he/she might not expect that.
		fprintf(stderr, "Fatal error: Path to save games too long.\n");
		exit(EXIT_FAILURE);
	}
	
	saveDir = realloc(saveDir, strlen(saveDir));

	// Create the path upto the save dir, if not already existing.
	mkdirhier (saveDir);
}

