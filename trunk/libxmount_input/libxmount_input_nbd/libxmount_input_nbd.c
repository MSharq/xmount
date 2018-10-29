
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h> /* sockaddr_un */
#include <stdbool.h> /* for bool datatype */
#include <signal.h> /* struct sigaction */
#include <getopt.h> /* for getopt_long; POSIX standard getopt is in unistd.h */
#include <errno.h>

#include "../libxmount_input.h"
#include "nbd.h"
#include "libxmount_input_nbd.h"

#define LOG_WARNING(...) {            \
	  LIBXMOUNT_LOG_WARNING(__VA_ARGS__); \
}

#define NBD_OPTION_WRITABLE "nbdwritable"
#define NBD_OPTION_DEFAULT_WRITABLE "false"

#define INIT_PASSWD "NBDMAGIC"
#define MY_NAME "nbd_client"
#define NBD_DEFAULT_PORT    "10809"

const uint64_t cliserv_magic = 0x00420281861253LL;
const uint64_t opts_magic = 0x49484156454F5054LL;
const uint64_t rep_magic = 0x3e889045565a9LL;

/*******************************************************************************
 *  * LibXmount_Input API implementation
 ******************************************************************************/
/*
 * LibXmount_Input_GetApiVersion
 */
uint8_t LibXmount_Input_GetApiVersion() {
  return LIBXMOUNT_INPUT_API_VERSION;
}

/*
 * LibXmount_Input_GetSupportedFormats
 */
const char* LibXmount_Input_GetSupportedFormats() {
  return "nbd\0dd\0\0";
}

/*
 * LibXmount_Input_GetFunctions
 */
void LibXmount_Input_GetFunctions(ts_LibXmountInputFunctions *p_functions) {
  printf("LibXmount_Input_GetFunctions in NBD\n");

  p_functions->CreateHandle=&NBDCreateHandle;
  p_functions->DestroyHandle=&NBDDestroyHandle;
  p_functions->Open=&NBDOpen;
  p_functions->Close=&NBDClose;
  p_functions->Size=&NBDSize;
  p_functions->Read=&NBDRead;
  p_functions->Write=&NBDWrite;
  p_functions->OptionsHelp=&NBDOptionsHelp;
  p_functions->OptionsParse=&NBDOptionsParse;
  p_functions->GetInfofileContent=&NBDGetInfofileContent;
  p_functions->GetErrorMessage=&NBDGetErrorMessage;
  p_functions->FreeBuffer=&NBDFreeBuffer;
}

/*******************************************************************************
 * Private
 ******************************************************************************/

/*
 *  * NBDCreateHandle
 *   */
static int NBDCreateHandle(void **pp_handle,
                           const char *p_format,
                           uint8_t debug)
{
  (void)p_format;
  char *p_nbd=NULL;
  uint16_t buff_size = 256;
  // 256 message buffer size
  
  printf("NBDCreateHandle function initiated\n");

  p_nbd=(char*)malloc(buff_size);
  if(p_nbd==NULL) return NBD_MEMALLOC_FAILED;

  memset(p_nbd,0,sizeof(buff_size));

  *pp_handle=p_nbd;
  return NBD_OK;
}

/*static int nbd_client_newstyle_handshake(struct nbd_client *client)
{
  struct nbd_newstyle_negotiation handshake;
  struct nbd_client_flags response;
  uint32_t client_flags;
  ssize_t len;
  int sock;

  sock = client->sock;

  while (true) {
    len = recv(sock, &handshake, sizeof handshake, MSG_WAITALL);
    if (client->disconnect)
      return FAILURE;
    if (len == -1 && errno == EINTR)
      continue;
    if (len != sizeof handshake)
      goto connection_fail;
    break;
  }

  nbd_newstyle_negotiation_ntoh(&handshake);

  if (!nbd_newstyle_negotiation_is_valid(&handshake)) {
    syslog(LOG_ERR, "%s: invalid handshake", __func__);
    nbd_newstyle_negotiation_dump(&handshake);
    return FAILURE;
  }

  client_flags = NBD_CLIENT_FLAG_FIXED_NEWSTYLE;
  if (handshake.handshake_flags & NBD_FLAG_NO_ZEROES)
    client_flags |= NBD_CLIENT_FLAG_NO_ZEROES;

  nbd_client_flags_set_client_flags(&response, client_flags);

  len = send(sock, &response, sizeof response, MSG_NOSIGNAL);
  if (len != sizeof response)
    goto connection_fail;

    client->flags = handshake.handshake_flags << 16;

  return SUCCESS;

  connection_fail:
    syslog(LOG_ERR, "%s: connection failed: %m", __func__);
    return FAILURE;
}*/



/*
 * NBDDestroyHandle
 */
static int NBDDestroyHandle(void **pp_handle) {
  
  printf("in NBDDestroyHandle function\n");
  free(*pp_handle);
  *pp_handle=NULL;
  return NBD_OK;
}

/*
 * NBDOpen
 */
static int NBDOpen(void *p_handle,
                   const char **pp_filename_arr,
                   uint64_t filename_arr_len)
{
  char* port = NBD_DEFAULT_PORT;
  int sock;
  int blocksize = 1024;
  char *hostname = NULL;
  int swap = 0;
  int cout = 0;
  int timeout = 0;
  int sdp =0;
  //int G_GNUC_UNUSED nofork = 0;
  int nofork = 0;
  pid_t main_pid;
  //u64 size64;
  unsigned long size64;
  uint16_t flags = 0;
  int c;
  int nonspecial = 0;
  int b_unix = 1; // we will set b_unix form the command line
  char* name = 0;
  uint16_t needed_flags;
  uint32_t cflags = 0;
  //uint32_t cflags = NBD_FLAG_C_FIXED_NEWSTYLE;
  uint32_t opts = 0;
  sigset_t block, old;
  char *certfile = NULL;
  char *keyfile = NULL;
  char *cacertfile = NULL;
  char *tlshostname = NULL;
  bool tls = false;
  struct sigaction sa;
  int num_connections = 1;
  //int netlink = HAVE_NETLINK;
  int need_disconnect = 0;
  int *scokfds;
  struct option long_options[] = {
  	{"unix", no_argument, NULL, 'u'},
  	{"version", no_argument, NULL, 'V'},
  	{"enable-tls", no_argument, NULL, 'x'},
  	{NULL,0,NULL,0}
  };
  
  struct sockaddr_un addr,serv_addr;
  int valread,count=0;
  int i;
  char buffer[1024] = {0};
  uint64_t magic;
  
  //hostname = argv[1];


  printf("NBDOpen got called----SRQ\n");

  for (i = 0; i < num_connections; i++) {
      if (b_unix)
            sock = openunix(hostname);
    else {
            printf("have to code for opennet i.e AF_INET family sockets\n");
            //printf("line:1222: going to opennet, port %s, sdp %d\n",port,sdp);
            //sock = opennet(hostname, port, sdp);
    }
    if (sock < 0)
            exit(EXIT_FAILURE);

    // handshake

    printf("line 1230: now code for the \"negotiate\" function\n");

    negotiate(&sock);
  }
  return NBD_OK;
}

/*
 * NBDClose
 */
static int NBDClose(void *p_handle) {
/*  t_pnbd    pnbd = (t_pnbd)p_handle;
  t_pPiece pPiece;
  int       CloseErrors = 0;

  printf("in NBDClose function\n");

  if (pnbd->pPieceArr)
  {
    for (uint64_t i=0; i < pnbd->Pieces; i++)
    {
      pPiece = &pnbd->pPieceArr[i];
      if (pPiece->pFile) {
        if (fclose (pPiece->pFile)) CloseErrors=1;
      }
      if (pPiece->pFilename) free (pPiece->pFilename);
    }
    free (pnbd->pPieceArr);
  }*/

//  if (CloseErrors) return NBD_CANNOT_CLOSE_FILE;

  return NBD_OK;
}

/*
 * NBDSize
 */
static int NBDSize(void *p_handle, uint64_t *p_size) {
/*  t_pnbd p_nbd_handle=(t_pnbd)p_handle;


  printf("in NBDSize function\n");

  *p_size=p_nbd_handle->TotalSize;*/
  return NBD_OK;
}

/*
 * NBDRead
 */
static int NBDRead(void *p_handle,
                   char *p_buf,
                   off_t seek,
                   size_t count,
                   size_t *p_read,
                   int *p_errno)
{
  return NBD_OK;
}

/*
 * NBDWrite
 */
static int NBDWrite(void *p_handle,
                    const char *p_buf,
                    off_t seek,
                    size_t count,
                    size_t *p_written,
                    int *p_errno)
{
  return NBD_OK;
}
/*
 * NBDOptionsHelp
 */
static int NBDOptionsHelp(const char **pp_help) {
  return NBD_OK;
}

/*
 * NBDOptionsParse
 */
static int NBDOptionsParse(void *p_handle,
                           uint32_t options_count,
                           const pts_LibXmountOptions *pp_options,
                           const char **pp_error)
{
  return NBD_OK;
}

/*
 * NBDGetInfofileContent
 */
static int NBDGetInfofileContent(void *p_handle, const char **pp_info_buf) {
  return NBD_OK;
}

/*
 * NBDGetErrorMessage
 */
static const char* NBDGetErrorMessage(int err_num) {

  printf("in NBDGetErrorMessage function\n");

  switch(err_num) {
    case NBD_MEMALLOC_FAILED:
      return "Unable to allocate memory";
      break;
    case NBD_FILE_OPEN_FAILED:
      return "Unable to open nbd file(s)";
      break;
    case NBD_CANNOT_READ_DATA:
      return "Unable to read nbd data";
      break;
    case NBD_CANNOT_WRITE_DATA:
      return "Unable to write nbd data";
      break;
    case NBD_CANNOT_CLOSE_FILE:
      return "Unable to close nbd file(s)";
      break;
    case NBD_CANNOT_SEEK:
      return "Unable to seek into nbd data";
      break;
    case NBD_READ_BEYOND_END_OF_IMAGE:
      return "Unable to read nbd data: Attempt to read past EOF";
      break;
    case NBD_WRITE_BEYOND_END_OF_IMAGE:
      return "Unable to write nbd data: Attempt to write past EOF";
      break;
    default:
      return "Unknown error";
  }
}

/*
 * NBDFreeBuffer
 */
static int NBDFreeBuffer(void *p_buf) {

  printf("in NBDFreeBuffer function\n");

  free(p_buf);
  return NBD_OK;
}

/*
 * Negotiate function
 */
void Negotiate(int *sockp) {
  //u64 magic;
  uint16_t handshake_flags;
  unsigned long int magic;
  char buff[256];
  int sock = *sockp;
  memset(&buff,'0',sizeof(buff));

  readit(sock,buff,8);
  if (strncmp(buff, INIT_PASSWD,8))
  {
    perror("init passwd wrong\n");
  }
  printf("init passwd received\n");
  readit(sock,&magic,sizeof(magic));
  magic = ntohll(magic);
  if (magic != opts_magic)
  {
    perror("magic number error, please remember old style handshake is not supported!\n");
  }
  printf("magic number received\n");

  readit(sock, &handshake_flags,sizeof(uint16_t));
  handshake_flags = ntohs(handshake_flags);
}

int readit(int f, void *buf, size_t len) {
  ssize_t res;
  while (len > 0) {
    //DEBUG("*");
    res = read(f, buf, len);
    if (res > 0) {
      len -= res;
      buf += res;
    } else if (res < 0) {
      if(errno != EAGAIN) {
      //err_nonfatal("Read failed: %m");
      printf("Read failed: %m");
      return -1;
      }
    } else {
      return -1;
    }
  }
  return 0;
}

int openunix(const char *path) {
  int fd;
  struct sockaddr_un serv_addr;

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
  {
          perror("\n Socket creation error \n");
          return -1;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;

  strncpy(serv_addr.sun_path, path, sizeof(serv_addr.sun_path)-1);

  if (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)  {
          perror("connect error\n");
          return -1;
  }

  return fd;
}

int opennet(char *name, char* portstr, int sdp) {
}

