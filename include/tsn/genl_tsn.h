// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/*
 * Copyright 2018-2019 NXP
 */

#ifndef __TSN_GENETLINK_H
#define __TSN_GENETLINK_H

#include <netlink/netlink.h>
#include <netlink/socket.h>
#include <netlink/msg.h>
#include <linux/netlink.h>
#include <linux/genetlink.h>
#include <time.h>
#include <cjson/cJSON.h>

#define MAX_MSGSIZE 256
#ifndef SOL_NETLINK
#define SOL_NETLINK 270
#endif

#ifndef NETLINK_LISTEN_ALL_NSID
#define NETLINK_LISTEN_ALL_NSID 8
#endif

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

typedef enum boolean {
	FALSE,
	TRUE,
} bool;

#define ptptime_t uint64_t
#define NUM_THREADS 100

#include <linux/tsn.h>

extern int VERBOSE;

#define _llog(file, fmt, ...) do { \
	if (VERBOSE) { \
		fprintf(file, "%s@%d: " fmt "\n", \
		__func__, __LINE__, ##__VA_ARGS__); \
	} else { \
		fprintf(file, fmt "\n", ##__VA_ARGS__); \
	} \
} while (0)

#define llogc(file, condition, ...) do { \
	if (condition) { \
		_llog(file, __VA_ARGS__); \
	} \
} while (0)

#define lloge(...) _llog(stderr, __VA_ARGS__)
#define llogi(...) _llog(stdout, __VA_ARGS__)
#define llogv(...) llogc(stdout, VERBOSE, __VA_ARGS__)

#if 0
#define	TSN_GENL_NAME		"TSN_GEN_CTRL"
#define	TSN_GENL_VERSION	0x1

#define MAX_USER_SIZE 0
#define MAX_ATTR_SIZE 3072
#define MAX_TOTAL_MSG_SIZE  (MAX_USER_SIZE + MAX_ATTR_SIZE)
#define MAX_ENTRY_SIZE 2048
#define MAX_ENTRY_NUMBER 128
#define MAX_IFNAME_COUNT 64
/*
 * Commands sent from userspace
 * Not versioned. New commands should only be inserted at the enum's end
 * prior to __TSN_CMD_MAX
 */

enum {
	TSN_CMD_UNSPEC = 0,	/* Reserved */
	TSN_CMD_QBV_SET,
	TSN_CMD_QBV_GET,
	TSN_CMD_QBV_GET_STATUS,
	TSN_CMD_CB_STREAMID_SET,
	TSN_CMD_CB_STREAMID_GET,
	TSN_CMD_CB_STREAMID_GET_COUNTS,
	TSN_CMD_QCI_CAP_GET, /* Qci capability get(length capability get) */
	TSN_CMD_QCI_SFI_SET,
	TSN_CMD_QCI_SFI_GET,
	TSN_CMD_QCI_SFI_GET_COUNTS,
	TSN_CMD_QCI_SGI_SET,
	TSN_CMD_QCI_SGI_GET,
	TSN_CMD_QCI_SGI_GET_STATUS,
	TSN_CMD_QCI_FMI_SET,
	TSN_CMD_QCI_FMI_GET,
	TSN_CMD_CBS_SET,
	TSN_CMD_CBS_GET,
	TSN_CMD_ECHO,			/* user->kernel request/get-response */
	TSN_CMD_REPLY,			/* kernel->user event */
	__TSN_CMD_MAX,
};
#define TSN_CMD_MAX (__TSN_CMD_MAX - 1)

enum {
	TSN_CMD_ATTR_UNSPEC = 0,
	TSN_CMD_ATTR_MESG,		/* demo message  */
	TSN_CMD_ATTR_DATA,		/* demo data */
	TSN_ATTR_IFNAME,
	TSN_ATTR_PORT_NUMBER,
	TSN_ATTR_QBV,
	TSN_ATTR_STREAM_IDENTIFY, /* stream identify */
	TSN_ATTR_QCI_SP,		/* psfp port capbility parameters */
	TSN_ATTR_QCI_SFI,		/* psfp stream filter instance */
	TSN_ATTR_QCI_SGI,		/* psfp stream gate instance */
	TSN_ATTR_QCI_FMI,		/* psfp flow meter instance */
	TSN_ATTR_CBS,			/* credit-based shaper */
	__TSN_CMD_ATTR_MAX,
};
#define TSN_CMD_ATTR_MAX (__TSN_CMD_ATTR_MAX - 1)

enum {
	TSN_CBS_ATTR_UNSPEC,
	TSN_CBS_ATTR_TC_INDEX,
	TSN_CBS_ATTR_BW,
	__TSN_CBS_ATTR_MAX,
	TSN_CBS_ATTR_MAX = __TSN_CBS_ATTR_MAX - 1,
};

enum {
	TSN_STREAMID_ATTR_UNSPEC,
	TSN_STREAMID_ATTR_INDEX,
	TSN_STREAMID_ATTR_ENABLE,
	TSN_STREAMID_ATTR_DISABLE,
	TSN_STREAMID_ATTR_STREAM_HANDLE,
	TSN_STREAMID_ATTR_SSID,
	TSN_STREAMID_ATTR_IFOP,
	TSN_STREAMID_ATTR_OFOP,
	TSN_STREAMID_ATTR_IFIP,
	TSN_STREAMID_ATTR_OFIP,
	TSN_STREAMID_ATTR_TYPE,
	TSN_STREAMID_ATTR_DMAC,
	TSN_STREAMID_ATTR_TAGGED,
	TSN_STREAMID_ATTR_VID,
	TSN_STREAMID_ATTR_COUNTERS_PSI,
	TSN_STREAMID_ATTR_COUNTERS_PSO,
	TSN_STREAMID_ATTR_COUNTERS_PSPPI,
	TSN_STREAMID_ATTR_COUNTERS_PSPPO,
	__TSN_STREAMID_ATTR_MAX,
	TSN_STREAMID_ATTR_MAX = __TSN_STREAMID_ATTR_MAX - 1,
};

enum {
	TSN_QCI_SFI_ATTR_UNSPEC,
	TSN_QCI_SFI_ATTR_INDEX,
	TSN_QCI_SFI_ATTR_ENABLE,
	TSN_QCI_SFI_ATTR_DISABLE,
	TSN_QCI_SFI_ATTR_STREAM_HANDLE,
	TSN_QCI_SFI_ATTR_PRIO_SPEC,
	TSN_QCI_SFI_ATTR_GATE_ID,
	TSN_QCI_SFI_ATTR_FILTER_TYPE,
	TSN_QCI_SFI_ATTR_FLOW_ID,
	TSN_QCI_SFI_ATTR_MAXSDU,
	TSN_QCI_SFI_ATTR_COUNTERS,
	TSN_QCI_SFI_ATTR_OVERSIZE_ENABLE,
	TSN_QCI_SFI_ATTR_OVERSIZE,
	__TSN_QCI_SFI_ATTR_MAX,
	TSN_QCI_SFI_ATTR_MAX = __TSN_QCI_SFI_ATTR_MAX - 1,
};

enum {
	TSN_QCI_SFI_ATTR_COUNTERS_UNSPEC,
	TSN_QCI_SFI_ATTR_MATCH,
	TSN_QCI_SFI_ATTR_PASS,
	TSN_QCI_SFI_ATTR_DROP,
	TSN_QCI_SFI_ATTR_SDU_DROP,
	TSN_QCI_SFI_ATTR_SDU_PASS,
	TSN_QCI_SFI_ATTR_RED,
	__TSN_QCI_SFI_ATTR_COUNT_MAX,
	TSN_QCI_SFI_ATTR_COUNT_MAX = __TSN_QCI_SFI_ATTR_COUNT_MAX - 1,
};

enum {
	TSN_QCI_SGI_ATTR_UNSPEC = 0,
	TSN_QCI_SGI_ATTR_INDEX,
	TSN_QCI_SGI_ATTR_ENABLE,
	TSN_QCI_SGI_ATTR_DISABLE,
	TSN_QCI_SGI_ATTR_CONFCHANGE,
	TSN_QCI_SGI_ATTR_IRXEN,		/* Invalid rx enable*/
	TSN_QCI_SGI_ATTR_IRX,
	TSN_QCI_SGI_ATTR_OEXEN,		/* Octet exceed enable */
	TSN_QCI_SGI_ATTR_OEX,
	TSN_QCI_SGI_ATTR_ADMINENTRY,
	TSN_QCI_SGI_ATTR_OPERENTRY,
	TSN_QCI_SGI_ATTR_CCTIME,	/* config change time */
	TSN_QCI_SGI_ATTR_TICKG,
	TSN_QCI_SGI_ATTR_CUTIME,
	TSN_QCI_SGI_ATTR_CPENDING,
	TSN_QCI_SGI_ATTR_CCERROR,
	__TSN_QCI_SGI_ATTR_MAX,
	TSN_QCI_SGI_ATTR_MAX = __TSN_QCI_SGI_ATTR_MAX - 1,
};

enum {
	TSN_SGI_ATTR_CTRL_UNSPEC = 0,
	TSN_SGI_ATTR_CTRL_INITSTATE,
	TSN_SGI_ATTR_CTRL_LEN,
	TSN_SGI_ATTR_CTRL_CYTIME,
	TSN_SGI_ATTR_CTRL_CYTIMEEX,
	TSN_SGI_ATTR_CTRL_BTIME,
	TSN_SGI_ATTR_CTRL_INITIPV,
	TSN_SGI_ATTR_CTRL_GCLENTRY,
	__TSN_SGI_ATTR_CTRL_MAX,
	TSN_SGI_ATTR_CTRL_MAX = __TSN_SGI_ATTR_CTRL_MAX - 1,
};

enum {
	TSN_SGI_ATTR_GCL_UNSPEC = 0,
	TSN_SGI_ATTR_GCL_GATESTATE,
	TSN_SGI_ATTR_GCL_IPV,
	TSN_SGI_ATTR_GCL_INTERVAL,
	TSN_SGI_ATTR_GCL_OCTMAX,
	__TSN_SGI_ATTR_GCL_MAX,
	TSN_SGI_ATTR_GCL_MAX = __TSN_SGI_ATTR_GCL_MAX - 1,
};

enum {
	TSN_QCI_FMI_ATTR_UNSPEC = 0,
	TSN_QCI_FMI_ATTR_INDEX,
	TSN_QCI_FMI_ATTR_CIR,
	TSN_QCI_FMI_ATTR_CBS,
	TSN_QCI_FMI_ATTR_EIR,
	TSN_QCI_FMI_ATTR_EBS,
	TSN_QCI_FMI_ATTR_CF,
	TSN_QCI_FMI_ATTR_CM,
	TSN_QCI_FMI_ATTR_DROPYL,
	TSN_QCI_FMI_ATTR_MAREDEN,
	TSN_QCI_FMI_ATTR_MARED,
	__TSN_QCI_FMI_ATTR_MAX,
	TSN_QCI_FMI_ATTR_MAX = __TSN_QCI_FMI_ATTR_MAX - 1,
};

enum {
	TSN_QBV_ATTR_UNSPEC,
	TSN_QBV_ATTR_ENABLE,
	TSN_QBV_ATTR_DISABLE,
	TSN_QBV_ATTR_CONFIGCHANGE,
	TSN_QBV_ATTR_CONFIGCHANGETIME,
	TSN_QBV_ATTR_MAXSDU,
	TSN_QBV_ATTR_GRANULARITY,
	TSN_QBV_ATTR_CURRENTTIME,
	TSN_QBV_ATTR_CONFIGPENDING,
	TSN_QBV_ATTR_CONFIGCHANGEERROR,
	TSN_QBV_ATTR_ADMINENTRY,
	TSN_QBV_ATTR_OPERENTRY,
	TSN_QBV_ATTR_LISTMAX,
	__TSN_QBV_ATTR_MAX,
	TSN_QBV_ATTR_MAX = __TSN_QBV_ATTR_MAX - 1,
};

enum {
	TSN_QBV_ATTR_CTRL_UNSPEC,
	TSN_QBV_ATTR_CTRL_LISTCOUNT,
	TSN_QBV_ATTR_CTRL_GATESTATE,
	TSN_QBV_ATTR_CTRL_CYCLETIME,
	TSN_QBV_ATTR_CTRL_CYCLETIMEEXT,
	TSN_QBV_ATTR_CTRL_BASETIME,
	TSN_QBV_ATTR_CTRL_LISTENTRY,
	__TSN_QBV_ATTR_CTRL_MAX,
	TSN_QBV_ATTR_CTRL_MAX = __TSN_QBV_ATTR_CTRL_MAX - 1,
};

enum {
	TSN_QBV_ATTR_ENTRY_UNSPEC,
	TSN_QBV_ATTR_ENTRY_ID,
	TSN_QBV_ATTR_ENTRY_GC,
	TSN_QBV_ATTR_ENTRY_TM,
	__TSN_QBV_ATTR_ENTRY_MAX,
	TSN_QBV_ATTR_ENTRY_MAX = __TSN_QBV_ATTR_ENTRY_MAX - 1,
};
#endif

#define MAX_NAME_LEN 100

struct info_type {
	char name[MAX_NAME_LEN];

};

struct qbv_multicast {
	uint64_t cct;
	uint32_t offset;
	int ifidx;
	bool en;
	void *callback_func;
	void *data;
};

struct qci_multicast {
	uint64_t cct;
	uint32_t offset;
	int ifidx;
	bool en;
	void *callback_func;
	void *data;
};

struct alarm_info {
	char *ptpdev[MAX_NAME_LEN];
	clockid_t clkid;
	struct {
		struct qbv_multicast qbvmc;
		struct qci_multicast qcimc;
	};
};

struct tsn_family_groups {
	uint16_t family_id;
	uint32_t mc[TSN_MCGRP_MAX];
	struct alarm_info *ai;
};

struct linkpara {
	int type;
	char len;
	char name[MAX_NAME_LEN];
};

struct showtable {
	int type;
	int len1;
	struct linkpara *link1;
	int len2;
	struct linkpara *link2;
	int len3;
	struct linkpara *link3;
};

struct tsn_cap {
	bool qbv;
	bool qci;
	bool qbu;
	bool cbs;
	bool cb;
	bool tbs;
	bool cut_through;
};
/*
 * Generic macros for dealing with netlink sockets. Might be duplicated
 * elsewhere. It is recommended that commercial grade applications use
 * libnl or libnetlink and use the interfaces provided by the library
 */

#define GENLMSG_ATTR_DATA(glh)	((void *)(NLMSG_DATA(glh) + GENL_HDRLEN + NLMSG_ALIGN(MAX_USER_SIZE)))
#define GENLMSG_ATTR_PAYLOAD(glh)	(NLMSG_PAYLOAD(glh, 0) - GENL_HDRLEN - NLMSG_ALIGN(MAX_USER_SIZE))
#define GENLMSG_USER_DATA(glh) ((void *)(NLMSG_DATA(glh) + GENL_HDRLEN))
#define NLA_DATA(na)		((void *)((char *)(na) + NLA_HDRLEN))
#define NLA_PAYLOAD(len)	(len - NLA_HDRLEN)

#define DEBUG	0

#define PRINTF(fmt, arg...) { \
	if (DEBUG) { \
		printf(fmt, ##arg); \
	} \
}

struct msgtemplate {
	struct nlmsghdr n;
	struct genlmsghdr g;
	char user[NLMSG_ALIGN(MAX_USER_SIZE)];
	char attr[NLMSG_ALIGN(MAX_ATTR_SIZE)];
};

typedef struct msgtemplate  msgtemplate_t;

struct global_conf {
	__u32 genl_fd;
	__u16 genl_familyid;
	__u32 pid;
};

extern struct global_conf glb_conf;

static inline struct nlattr *tsn_nla_nest_start(struct msgtemplate *msg, __u16 nla_type)
{
	struct nlattr *na;

	na = (struct nlattr *)((char *)msg + (msg->n.nlmsg_len));

	na->nla_type = nla_type;
	na->nla_len = NLA_HDRLEN;

	msg->n.nlmsg_len += NLMSG_ALIGN(na->nla_len);

	return na;
}

static inline int tsn_nla_nest_end(struct msgtemplate *msg, struct nlattr *start)
{
	start->nla_len = (char *)msg + (msg->n.nlmsg_len) - (char *)start;

	return msg->n.nlmsg_len;
}

struct msgtemplate *tsn_send_cmd_prepare(__u8 genl_cmd);
void tsn_send_cmd_append_attr(struct msgtemplate *msg, __u16 nla_type, void *nla_data, int nla_len);
int tsn_send_to_kernel(struct msgtemplate *msg);
int tsn_msg_recv_analysis(struct showtable *linkdata, void *para);

int genl_tsn_init(void);
void genl_tsn_close(void);
int tsn_echo_test(char *string, int data);

int tsn_capability_get(char *portname, struct tsn_cap *cap);
int tsn_qos_port_qbv_set(char *portname, struct tsn_qbv_conf *adminconf, bool enable);
int tsn_qos_port_qbv_get(char *portname, struct tsn_qbv_conf *qbvconf);
int tsn_qos_port_qbv_status_get(char *portname, struct tsn_qbv_status *qbvstaus);
int tsn_qci_streampara_get(char *portname,
				      struct tsn_qci_psfp_stream_param *sp);
int tsn_cb_streamid_set(char *portname, uint32_t sid_index, bool enable,
		struct tsn_cb_streamid *sid);
int tsn_cb_streamid_get(char *portname, uint32_t sid_index, struct tsn_cb_streamid *sid);
int tsn_qci_psfp_sfi_get(char *portname, uint32_t sfi_handle,
						struct tsn_qci_psfp_sfi_conf *sfi);
int tsn_qci_psfp_sfi_set(char *portname, uint32_t sfi_handle, bool enable,
							struct tsn_qci_psfp_sfi_conf *sfi);

int tsn_qci_psfp_sgi_set(char *portname, uint32_t sgi_handle, bool enable,
						struct tsn_qci_psfp_sgi_conf *sgi);
int tsn_qci_psfp_sgi_get(char *portname, uint32_t sgi_handle, struct tsn_qci_psfp_sgi_conf *sgi);
int tsn_qci_psfp_sgi_status_get(char *portname, uint32_t sgi_handle, struct tsn_psfp_sgi_status *sgi);
int tsn_qci_psfp_fmi_set(char *portname, uint32_t fmi_id, bool enable, struct tsn_qci_psfp_fmi *fmiconf);
int tsn_qci_psfp_fmi_get(char *portname, uint32_t fmi_id, struct tsn_qci_psfp_fmi *fmiconf);
int tsn_cbs_set(char *portname, uint8_t tc, uint8_t percent);
int tsn_cbs_get(char *portname, uint8_t tc);
int tsn_tsd_set(char *portname, bool enable, uint32_t period, uint32_t frame_num, bool imme);
int tsn_tsd_get(char *portname);
int tsn_qbu_set(char *portname, uint8_t pt_vector);
int tsn_qbu_get_status(char *portname, struct tsn_preempt_status *pts);
int tsn_ct_set(char *portname, uint8_t pt_vector);
int tsn_cbgen_set(char *portname, uint32_t index, struct tsn_seq_gen_conf *sg);
int tsn_cbrec_set(char *portname, uint32_t index, struct tsn_seq_rec_conf *sr);
int tsn_cbstatus_get(char *portname, uint32_t index,
		     struct tsn_cb_status *cbstat);
int tsn_dscp_set(char *portname, bool disable, int index,
		 struct tsn_qos_switch_dscp_conf *dscp_conf);
int64_t pctns(struct timespec *t);
int get_net_ifindex_by_name(const char *eth_name, uint32_t *ifindex);
int set_period_alarm(uint64_t ts, uint64_t offset,
		     uint64_t cycle, void (*callback_func)(void *data), void *data);
pthread_t *create_alarm_common(uint64_t ts, uint32_t offset, uint32_t cycle,
			      void (*callback_func)(void *data), void *data);
int delete_alarm_common(pthread_t *thread);
int wait_tsn_multicast();
void get_para_from_json(int type, cJSON *json, void *para);

#endif /* _TSN_GENETLINK_KERN_H */
