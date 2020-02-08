#ifndef SPACIALFREEZE_ERROR_H
#define SPACIALFREEZE_ERROR_H
/**
 * Checks for errors and prints them out, replacing the glCheckError function with this new one
 * @return Enum (String) representing the error that occurred
 */
GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLenum glCheckError_(const char *file, int line);

#endif //SPACIALFREEZE_ERROR_H
