#if !defined(__APPLE__) && !defined(__linux__)
#error "It does not support this yet"
#endif

#define COMPILER "gcc"

#ifdef RELEASE
#define OPTIONS "-std=c11 -O3 -Wall -Wextra -Wpedantic"
#else
#define OPTIONS "-std=c11 -O0 -ggdb -Wall -Wextra -Wpedantic"
#endif

#define AEDIF_IMPLEMENTATION
#include "aedif.h"

#define DRAPEAU_IMPLEMENTATION
#include "lib/drapeau/drapeau.h"

const char* srcs[] = {
    "./src/main.c",
    NULL,
};

const char* includes[] = {
    "./src",
    NULL,
};

int main(int argc, char** argv)
{
    drapeauStart("aedif", "danxe builder");

    bool* is_clean = drapeauSubcmd("clean", "clean builder");
    bool* is_build = drapeauSubcmd("build", "build project");

    drapeauParse(argc, argv);
    drapeauClose();

    if (drapeauIsHelp() || (!*is_clean && !*is_build))
    {
        drapeauPrintHelp();
        return 0;
    }

    if (*is_clean)
    {
        cleanBuild();
        return 0;
    }

    if (*is_build)
    {
        buildProject(false, "danxe", OPTIONS, srcs, includes, NULL, NULL, NULL);
        return 0;
    }
}
