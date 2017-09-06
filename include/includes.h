// C/C++ stdlib includes
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// this is used to make sure, certain files are only loaded if compiled in C++
#ifdef __cplusplus
	#include <iostream>
	#include <string>
	#include <vector>
	#include <fstream>
	#include <streambuf>
#else
	#include <string.h> // we still have to include strings though
#endif

// 3ds includes
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include <sftd.h>

// homebrew_os includes
#include "definitions.h"

#ifdef __cplusplus
	#include "io.h"
	#include "ui/menu.h"
	#include "ui/recovery/recoveryMenu.h"
#endif

// these are files from fincs' new hb menu that I still have to re-write.
// since they are written in C only, I have to use `extern "C"`
#ifdef __cplusplus
	extern "C" {
#endif
		#include "launch.h"
		#include "menu.h"
#ifdef __cplusplus
	}
#endif
