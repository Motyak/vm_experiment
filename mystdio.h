#ifndef MYSTDIO_H
#define MYSTDIO_H

#ifndef __GLIBC__
#error "glibc required for mystdio to be used"
#endif

#define __USE_POSIX 1 // required for fileno()

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/*
    Changes compared to fseek:
    - we call lseek only, not fstat nor read.
    - "POSIX allows seeking beyond the existing end of file.
       If an output is performed after this seek, any read from the gap will return zero bytes.
       Where supported by the filesystem, this creates a sparse file."
         -> if we seek beyond file (whether after end or before begin)
            => we return -1
    - "POSIX also requires that fseek first performs fflush if there are any unwritten data
       (but whether the shift state is restored is implementation-defined)."
         -> we don't perform fflush
*/
int my_fseek(FILE* file, long int offset, int whence) {
    int fd = fileno(file);
    off_t new_offset = lseek(fd, offset, whence);
    if (new_offset == -1) {
        return -1;
    }
    file->_offset = new_offset;
    return 0;
}



#endif // MYSTDIO_H
