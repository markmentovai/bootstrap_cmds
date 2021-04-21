#ifndef BOOTSTRAP_CMDS_COMPAT_NON_APPLE_MACH_NDR_H_
#define BOOTSTRAP_CMDS_COMPAT_NON_APPLE_MACH_NDR_H_

typedef struct {
  unsigned char mig_vers;
  unsigned char if_vers;
  unsigned char reserved1;
  unsigned char mig_encoding;
  unsigned char int_rep;
  unsigned char char_rep;
  unsigned char float_rep;
  unsigned char reserved2;
} NDR_record_t;

#endif  /* BOOTSTRAP_CMDS_COMPAT_NON_APPLE_MACH_NDR_H_ */
