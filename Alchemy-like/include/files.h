#ifndef FILES
#define FILES


int size_index(int fd);
int indopen(const char *path, int flags, int ind, mode_t mode);
int indclose(int fd);
ssize_t indread(int fd, void *buf, size_t nbytes);
ssize_t indwrite(int fd, const void *buf, size_t nbytes);
off_t indlseek(int fd, off_t offset, int whence);


#endif
