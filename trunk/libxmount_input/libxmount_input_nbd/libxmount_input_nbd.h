
#ifndef LIBXMOUNT_INPUT_NBD_H
#define LIBXMOUNT_INPUT_NBD_H

#if __BIG_ENDIAN__
    #define htonll(x)   (x)
    #define ntohll(x)   (x)
#else
    #define htonll(x)   ((((uint64_t)htonl(x&0xFFFFFFFF)) << 32) + htonl(x >> 32))
    #define ntohll(x)   ((((uint64_t)ntohl(x&0xFFFFFFFF)) << 32) + ntohl(x >> 32))
#endif

/*******************************************************************************
 *  * Error codes etc...
 *   ******************************************************************************/
enum {
  NBD_OK=0,
  NBD_MEMALLOC_FAILED,
  NBD_FILE_OPEN_FAILED,
  NBD_CANNOT_READ_DATA,
  NBD_CANNOT_WRITE_DATA,
  NBD_CANNOT_CLOSE_FILE,
  NBD_CANNOT_SEEK,
  NBD_READ_BEYOND_END_OF_IMAGE,
  NBD_WRITE_BEYOND_END_OF_IMAGE,
};


/*******************************************************************************
 * Forward declarations
 ******************************************************************************/
static int NBDCreateHandle(void **pp_handle,
                           const char *p_format,
                           uint8_t debug);
static int NBDDestroyHandle(void **pp_handle);
static int NBDOpen(void *p_handle,
                   const char **pp_filename_arr,
                   uint64_t filename_arr_len);
static int NBDClose(void *p_handle);
static int NBDSize(void *p_handle,
                   uint64_t *p_size);
static int NBDRead(void *p_handle,
                   char *p_buf,
                   off_t seek,
                   size_t count,
                   size_t *p_read,
                   int *p_errno);
static int NBDWrite(void *p_handle,
                    const char *p_buf,
                    off_t seek,
                    size_t count,
                    size_t *p_written,
                    int *p_errno);
static int NBDOptionsHelp(const char **pp_help);
static int NBDOptionsParse(void *p_handle,
                           uint32_t options_count,
                           const pts_LibXmountOptions *pp_options,
                           const char **pp_error);
static int NBDGetInfofileContent(void *p_handle,
                                 const char **pp_info_buf);
static const char* NBDGetErrorMessage(int err_num);
static int NBDFreeBuffer(void *p_buf);

void negotiate(int *sockp);

/* read data from file descriptor into the buffer
 * @f is file descriptor
 * @buf a buffer
 * @len the number of byter to read
 * return 0 on completion, -1 on failure
 **/
int readit(int f,void *buf,size_t len);

int writeit(int f,void *buf,size_t len);

int openunix(const char *path);
int opennet(char *name, char* portstr, int sdp);

#endif // LIBXMOUNT_INPUT_NBD_H
