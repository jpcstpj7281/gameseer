/* secEnd.h - Atmel AT91RM9200 Ethernet network interface header */



#ifndef __INCsecEndh
#define __INCsecEndh

#ifdef  __cplusplus
extern "C" {
#endif


/* END Specific Definitions */

#define SEC_END_DEV_NAME                ETH_DEV_NAME
#define SEC_END_DEV_NAME_LEN            ETH_DEV_NAME_LEN
#define SEC_END_DEV_DESCRIPTION         ETH_DEV_DESCRIPTION

#define SEC_END_ADDR_LEN                6
#define END_HADDR(pEndObj)              ((pEndObj)->mib2Tbl.ifPhysAddress.phyAddress)

#define SEC_END_NUM_CL_TYPE             1                   /* number of clusters types */
#define CL_OVERHEAD                     (sizeof(int))       /* cluster overhead */
#define CL_ALIGNMENT                    4                   /* cluster required alignment */
#define MBLK_ALIGNMENT                  4                   /* mBlks required alignment */
			

/* Function Prototypes */

IMPORT END_OBJ* secEndLoad(char *initString);


/* Helper Macros */

typedef ETH_DRV_CTRL DRV_CTRL;

#define DRV_CLUSTER_MEM_BASE            FB_BASE_ETH
#define DRV_CLUSTER_MEM_SIZE            FB_SIZE_ETH
#define DRV_SIZE_CLUSTER                SIZE_ETH_MDMA
#define DRV_SIZE_CLUSTER_HDR            SIZE_ETH_FB_HDR
#define DRV_NUM_CLUSTER                 ((NUM_BD_ETH) + (NUM_RBD_ETH))
#define DRV_NUM_MBLK                    (DRV_NUM_CLUSTER*2)

#define DRV_INIT                        at91EthInit
#define DRV_ADDR_SET                    update_mac_address
#define DRV_FLAGS_SET                   at91EthFlagsSet
#define DRV_LOOP_SET                    at91EthLoopSet
#define DRV_MCAST_ADD                   at91EthMCastAdd
#define DRV_MCAST_DEL                   at91EthMCastDel

#define DRV_START                       at91EthStart
#define DRV_STOP                        at91EthStop
#define DRV_POLL_START                  at91EthPollStart
#define DRV_POLL_STOP                   at91EthPollStop

/*#define DRV_RBD_GET                     at91EthRbdGet
#define DRV_RBD_FREE                    at91EthRbdFree
#define DRV_RBD_CHECK                   at91EthRbdCheck

#define DRV_TBD_GET                     at91EthTbdGet
#define DRV_TBD_FREE                    at91EthTbdFree
#define DRV_TBD_START                   at91EthTbdStart
#define DRV_TBD_CHECK                   at91EthTbdCheck
*/
#define DRV_POLL_RECEIVE                at91EthPollReceive
#define DRV_POLL_SEND                   at91EthPollSend

#define DRV_SEND                        at91EthSend


#ifdef __cplusplus
}
#endif

#endif  /* __INCsecEndh */

