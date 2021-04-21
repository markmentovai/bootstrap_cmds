#ifndef BOOTSTRAP_CMDS_COMPAT_NON_APPLE_MACH_MESSAGE_H_
#define BOOTSTRAP_CMDS_COMPAT_NON_APPLE_MACH_MESSAGE_H_

#include <mach/port.h>
#include <mach/machine/vm_types.h>
#include <mach/port.h>

typedef unsigned int mach_msg_bits_t;
typedef natural_t mach_msg_size_t;
typedef integer_t mach_msg_id_t;

typedef unsigned int mach_msg_type_name_t;

#define MACH_MSG_TYPE_MOVE_RECEIVE 16
#define MACH_MSG_TYPE_MOVE_SEND 17
#define MACH_MSG_TYPE_MOVE_SEND_ONCE 18
#define MACH_MSG_TYPE_COPY_SEND 19
#define MACH_MSG_TYPE_MAKE_SEND 20
#define MACH_MSG_TYPE_MAKE_SEND_ONCE 21

typedef unsigned int mach_msg_descriptor_type_t;

#define MACH_MSG_PORT_DESCRIPTOR 0
#define MACH_MSG_OOL_DESCRIPTOR 1
#define MACH_MSG_OOL_PORTS_DESCRIPTOR 2

typedef struct {
  mach_msg_size_t msgh_descriptor_count;
} mach_msg_body_t;

typedef struct {
  mach_msg_bits_t msgh_bits;
  mach_msg_size_t msgh_size;
  mach_port_t msgh_remote_port;
  mach_port_t msgh_local_port;
  mach_port_name_t msgh_voucher_port;
  mach_msg_id_t msgh_id;
} mach_msg_header_t;

typedef natural_t mach_msg_type_number_t;

#define MACH_MSG_TYPE_PORT_NAME 15
#define MACH_MSG_TYPE_PORT_RECEIVE MACH_MSG_TYPE_MOVE_RECEIVE
#define MACH_MSG_TYPE_PORT_SEND MACH_MSG_TYPE_MOVE_SEND
#define MACH_MSG_TYPE_PORT_SEND_ONCE MACH_MSG_TYPE_MOVE_SEND_ONCE

#define MACH_MSG_TYPE_POLYMORPHIC ((mach_msg_type_name_t) -1)

#define MACH_MSG_TYPE_PORT_ANY(x)            \
    (((x) >= MACH_MSG_TYPE_MOVE_RECEIVE) &&  \
     ((x) <= MACH_MSG_TYPE_MAKE_SEND_ONCE))

#endif  /* BOOTSTRAP_CMDS_COMPAT_NON_APPLE_MACH_MESSAGE_H_ */
