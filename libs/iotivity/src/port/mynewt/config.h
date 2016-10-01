#ifndef CONFIG_H
#define CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

/* Time resolution */
#include <stdint.h>
#include <os/os.h>
#include <log/log.h>
#include <syscfg/syscfg.h>

/* rather than change all their source files, just translate the mynewt
 * package defines into their defines here */
#if (MYNEWT_VAL(OC_SERVER) == 1)
#define OC_SERVER
#endif

#if (MYNEWT_VAL(OC_CLIENT) == 1)
#define OC_CLIENT
#endif

#if (MYNEWT_VAL(OC_DEBUG) == 1)
#define DEBUG 1
#endif

extern struct log oc_log;

typedef os_time_t oc_clock_time_t;
#define OC_CLOCK_CONF_TICKS_PER_SECOND (OS_TICKS_PER_SEC)
#ifdef ARCH_sim
#define OC_CLK_FMT  "%u"
#else
#define OC_CLK_FMT  "%lu"
#endif

/* Memory pool sizes */
#define OC_BYTES_POOL_SIZE (2048)
#define OC_INTS_POOL_SIZE (16)
#define OC_DOUBLES_POOL_SIZE (16)

/* Server-side parameters */
/* Maximum number of server resources */
#define MAX_APP_RESOURCES (8)

/* Common paramters */
/* Maximum number of concurrent requests */
#define MAX_NUM_CONCURRENT_REQUESTS (2)

/* Estimated number of nodes in payload tree structure */
#define EST_NUM_REP_OBJECTS (100)

/* Maximum size of request/response PDUs */
#define MAX_PAYLOAD_SIZE (612)

/* Number of devices on the OCF platform */
#define MAX_NUM_DEVICES (1)

/* Platform payload size */
#define MAX_PLATFORM_PAYLOAD_SIZE (256)

/* Device payload size */
#define MAX_DEVICE_PAYLOAD_SIZE (256)

/* Security layer */
/* Maximum number of authorized clients */
//#define MAX_NUM_SUBJECTS (2)

/* Maximum number of concurrent DTLS sessions */
//#define MAX_DTLS_PEERS (1)

/* Max inactivity timeout before tearing down DTLS connection */
//#define DTLS_INACTIVITY_TIMEOUT (10)

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H */
