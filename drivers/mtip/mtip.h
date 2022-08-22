//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_H
#define _MTIP_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/netdevice.h>

#include "ecpri_dma_eth.h"
#include "eth_ecpriss_iface.h"
#include "macsec_eth.h"

#define DRV_NAME "csm-mtip"

#include "mtip_logging.h"
#include "eth_phy_iface.h"
#include "mtip_ptp.h"
#include "mtip_client.h"
#include "mtip_clocks.h"

// the driver name
#define MTIP_MAC_DRIVER                 "MTIP_MAC"
#define MTIP_MAC_DRIVER_VERSION         "1.0.0"

// Common feature definitions

/* if loopback is enabled then SWAP_HANDLE will swap the handle of Rx/Tx interfaces */
#define MTIP_LOOPBACK_SWAP_HANDLE

/* if loopback is enabled then SWAP_ADDRESSES will swap DA/SA */
#define MTIP_LOOPBACK_SWAP_ADDRESSES

/* Dump the contents of Tx and Rx skbs */
//#define MTIP_DUMP_PACKETS

/* Setting the modes of the driver */
#define MTIP_MODE_DEFAULT          0   // This is the default mode with no loopback
#define MTIP_MODE_LOOPBACK         1   // This is the loopback mode. For RUMI, this is IOMACRO loopback and for SOC it is PCS LOOPBACK
#define MTIP_MODE_PHY_LOOPBACK     2   // This is the PHY loopback mode for SOC. Not applicable for RUMI

/* System Configuration */
#define MTIP_MAX_PORTS  7          // Max of 7 ports allowed in the system
#define MTIP_MAX_LINKS  16         // Setup for a max of 16 Ethernet links
#define MTIP_MAX_LINKS_PER_PORT 4  // Max of 4 links per port

/* Networking Stack Configuration */
#define MTIP_TIMEOUT     5 /* in Jiffies*/
#define MTIP_NAPI_WEIGHT 64 /* Initial NAPI weight */

// the range of supported MTU sizes
#define MTIP_MIN_MTU_SIZE  68
#define MTIP_MAX_MTU_SIZE  1536

#define MTIP_DMA_RX_PACKET_SIZE 1600 /* use buffers of size 1600 */

#define MTIP_TX_RING_SIZE 100
#define MTIP_RX_RING_SIZE 100

#define MTIP_TX_MOD_COUNTER_THRESHOLD 1       // RECOMMENDED VALUE: 25% of RING SIZE
#define MTIP_TX_MOD_TIMER_THRESHOLD   0       // RECOMMENDED VALUE: 10 msec

#define MTIP_TX_PACKET_AVAILABILITY_THRESHOLD     10

#define MTIP_TSC_OFFSET_VAL          0x00000013  // TSC OFFSET REGISTER VALUE TO BE SET AFTER BRING UP IS COMPLETE
#define MTIP_DEBUG_ETH_LINK_INDEX     15
/*
 * Information related to the devices in the device tree
 */
// the information stored for each link device
struct mtip_link_device_info
{
    // the port device platform device
    struct platform_device* link_pdev;

    // the link phandle
    u32 link_phandle;

    // link indices
    u32 link_index;

    // link lane speed
    enum eth_phy_iface_phy_lane_speed_enum  lane_speed;

    // the number of assigned lanes
    u32                   num_lanes;

    // link lane assignments
    u8                    lanes[PHY_LANE_MAX];

    // link base mac register address
    void __iomem           *mac_ioaddr;

    // link base pcs register address
    void __iomem           *pcs_ioaddr;

    // store the name of the interface
    const char*            link_name;
};

// the information stored for each port device
struct mtip_port_device_info
{
    // the port device platform device
    struct platform_device* port_pdev;

    // the phandle of the port device
    u32 port_phandle;

   // the port type
   u32 port_type;

   // the base address for the MAC Wrapper
   void __iomem          *wrapper_base_addr;

   // the base address for the MACSTATS CONTROL
   void __iomem          *macstats_base_addr;

   // the base address for the RSFEC
   void __iomem          *rsfec_base_addr;

   // the irq for MAC wrapper
   u32 wrapper_irq;

   // Base address for emulation DUT(FH instance)
   void __iomem          *dut_base_addr;

   // consolidate port lane configuration
   struct eth_phy_iface_phy_lane_config lane_config[PHY_LANE_MAX];

   // the references to links of the port
   u32 num_link_phandles;
   u32 num_link_phandles_probed;
   u32 link_phandles[MTIP_MAX_LINKS_PER_PORT];

   // the link devices
   struct mtip_link_device_info link_devices[MTIP_MAX_LINKS_PER_PORT];
};

/*
 * The root device that contains all the other devices
 */
struct mtip_devices_info
{
    // the root platform device
    struct platform_device* root_pdev;

    // device mode
    enum mtip_device_mode_enum mode;

    // the base address for the MAC Address fuses
    void __iomem          *fuse_base_addr;

    // the bit offset at the fuse address where the MAC address starts
    u8  fuse_bit_offset;

    // the port phandles
    u32 num_port_phandles;
    u32 num_port_phandles_probed;
    u32 port_phandles[MTIP_MAX_PORTS];

    // the port devices
    struct mtip_port_device_info port_devices[MTIP_MAX_PORTS];
};

/*
 * information stored for each active link including netdev struct etc
 */
/*
 * mtip_link_state enum
 */
enum mtip_link_state_enum
{
   MTIP_LINK_STATE_INIT = 0,
   MTIP_LINK_STATE_OPEN,
   MTIP_LINK_STATE_CLOSE,
   MTIP_LINK_STATE_UP,
   MTIP_LINK_STATE_DOWN,
   MTIP_LINK_STATE_MAX
};

struct mtip_link_info
{
   enum mtip_link_state_enum state;
   struct net_device* dev;
   struct napi_struct napi;
   struct rtnl_link_stats64 net_stats;
   ecpri_dma_eth_conn_hdl_t dma_hdl;
   u32 port_device_index;
   u32 link_device_index;
   bool ptp_ts_enabled;
   struct mtip_tx_ts_list tx_ts_list;
   struct mtip_tx_ts_skb_list tx_ts_skb_list;
   struct mutex dev_lock;
};

// platform struct private
struct mtip_platform_driver_priv
{
   // the platform driver error status
   int perr;

   // devices information
   // this gets filled up as device probes are received
   struct mtip_devices_info devices;

   // store the clocks here
   struct mtip_clocks_clock_struct clocks;

   // information stored for each active link including netdev structs etc
   struct mtip_link_info* mtip_links[MTIP_MAX_LINKS];

   // dma ready state
   bool dma_is_ready;

   // phy ready state
   bool phy_is_ready;

	// the system topology
	eth_ecpriss_topology_root_s* topology;

    // macsec ops
    struct macsec_ops* security_macsec_ops;

   // the clients registered
   struct mtip_client_struct clients[MTIP_MAX_CLIENTS];

    // the spin lock to access driver priv
    spinlock_t driver_lock;
};

// extern declarations
extern struct mtip_platform_driver_priv* platform_driver_priv;

// this is the extern to connect to dma driver
extern struct ecpri_dma_eth_ops ecpri_dma_eth_driver_ops;

// this is the extern controlling loopback mode
extern int mtip_loopback_mode;

// this is the extern to set if we are running on a RUMI
extern int mtip_rumi_platform;

// function prototypes
int mtip_register_platform_driver(void);
int mtip_lookup_link_index_by_name(char* name, u32* link_index);
int mtip_lookup_link_index_by_handle(ecpri_dma_eth_conn_hdl_t hdl, u32* link_index);

int mtip_lookup_link_index_by_device(u32* link_index, u32 port_device_index, u32 link_device_index);
int mtip_lookup_device_by_link_index(u32 link_index, u32* port_device_index, u32* link_device_index);

int mtip_lookup_link_index_by_real_port_and_link(u32* link_index, u32 real_port_number, u32 real_link_number);
int mtip_lookup_real_link_number_by_link_index(u32 link_index, u32* link_number);

#endif // _MTIP_H
