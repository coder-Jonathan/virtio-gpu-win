#pragma once
#include "helper.h"

enum virtio_gpu_ctrl_type {
    VIRTIO_GPU_UNDEFINED = 0,

    /* 2d commands */
    VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100,
    VIRTIO_GPU_CMD_RESOURCE_CREATE_2D,
    VIRTIO_GPU_CMD_RESOURCE_UNREF,
    VIRTIO_GPU_CMD_SET_SCANOUT,
    VIRTIO_GPU_CMD_RESOURCE_FLUSH,
    VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
    VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
    VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING,
    VIRTIO_GPU_CMD_GET_CAPSET_INFO,
    VIRTIO_GPU_CMD_GET_CAPSET,

    /* 3d commands */
    VIRTIO_GPU_CMD_CTX_CREATE = 0x0200,
    VIRTIO_GPU_CMD_CTX_DESTROY,
    VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE,
    VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE,
    VIRTIO_GPU_CMD_RESOURCE_CREATE_3D,
    VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D,
    VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D,
    VIRTIO_GPU_CMD_SUBMIT_3D,

    /* cursor commands */
    VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300,
    VIRTIO_GPU_CMD_MOVE_CURSOR,

    /* success responses */
    VIRTIO_GPU_RESP_OK_NODATA = 0x1100,
    VIRTIO_GPU_RESP_OK_DISPLAY_INFO,
    VIRTIO_GPU_RESP_OK_CAPSET_INFO,
    VIRTIO_GPU_RESP_OK_CAPSET,

    /* error responses */
    VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200,
    VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY,
    VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID,
    VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID,
    VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID,
    VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER,
};

#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)

enum virtio_gpu_formats {
    VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM  = 1,
    VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM  = 2,
    VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM  = 3,
    VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM  = 4,

    VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM  = 67,
    VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM  = 68,

    VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM  = 121,
    VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM  = 134,
};

enum opengl_icd_cmd {
    OPENGL_ICD_CMD_INVALID = 0,
    OPENGL_ICD_CMD_TRANSFER = 1,
    OPENGL_ICD_CMD_ALLOCATE,
    OPENGL_ICD_CMD_UPDATE,
    OPENGL_ICD_CMD_FREE,
};

#pragma pack(1)
typedef struct virtio_gpu_rect {
    ULONG x;
    ULONG y;
    ULONG width;
    ULONG height;
}GPU_RECT, *PGPU_RECT;
#pragma pack()

#define VIRTIO_GPU_FLAG_FENCE (1 << 0)

#pragma pack(1)
typedef struct virtio_gpu_ctrl_hdr {
    ULONG type;
    ULONG flags;
    ULONGLONG fence_id;
    ULONG ctx_id;
    ULONG padding;
}GPU_CTRL_HDR, *PGPU_CTRL_HDR;
#pragma pack()

#pragma pack(1)
typedef struct virtio_gpu_display_one {
    GPU_RECT r;
    ULONG enabled;
    ULONG flags;
}GPU_DISP_ONE, *PGPU_DISP_ONE;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_UNREF */
#pragma pack(1)
typedef struct virtio_gpu_resource_unref {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG padding;
}GPU_RES_UNREF, *PGPU_RES_UNREF;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_2D: create a 2d resource with a format */
#pragma pack(1)
typedef struct virtio_gpu_resource_create_2d {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG format;
    ULONG width;
    ULONG height;
}GPU_RES_CREATE_2D, *PGPU_RES_CREATE_2D;
#pragma pack()

/* VIRTIO_GPU_CMD_SET_SCANOUT */
#pragma pack(1)
typedef struct virtio_gpu_set_scanout {
    GPU_CTRL_HDR hdr;
    GPU_RECT r;
    ULONG scanout_id;
    ULONG resource_id;
}GPU_SET_SCANOUT, *PGPU_SET_SCANOUT;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_FLUSH */
#pragma pack(1)
typedef struct virtio_gpu_resource_flush {
    GPU_CTRL_HDR hdr;
    GPU_RECT r;
    ULONG resource_id;
    ULONG padding;
}GPU_RES_FLUSH, *PGPU_RES_FLUSH;
#pragma pack()

/* VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D: simple transfer to_host */
#pragma pack(1)
typedef struct virtio_gpu_transfer_to_host_2d {
    GPU_CTRL_HDR hdr;
    GPU_RECT r;
    ULONGLONG offset;
    ULONG resource_id;
    ULONG padding;
}GPU_RES_TRANSF_TO_HOST_2D, *PGPU_RES_TRANSF_TO_HOST_2D;
#pragma pack()

#pragma pack(1)
typedef struct virtio_gpu_mem_entry {
    ULONGLONG addr;
    ULONG length;
    ULONG padding;
}GPU_MEM_ENTRY, *PGPU_MEM_ENTRY;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING */
#pragma pack(1)
typedef struct virtio_gpu_resource_attach_backing {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG nr_entries;
}GPU_RES_ATTACH_BACKING, *PGPU_RES_ATTACH_BACKING;
#pragma pack()

/* VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING */
#pragma pack(1)
typedef struct virtio_gpu_resource_detach_backing {
    GPU_CTRL_HDR hdr;
    ULONG resource_id;
    ULONG padding;
}GPU_RES_DETACH_BACKING, *PGPU_RES_DETACH_BACKING;
#pragma pack()

/* VIRTIO_GPU_RESP_OK_DISPLAY_INFO */
#define VIRTIO_GPU_MAX_SCANOUTS 16
#pragma pack(1)
typedef struct virtio_gpu_resp_display_info {
    GPU_CTRL_HDR hdr;
    GPU_DISP_ONE pmodes[VIRTIO_GPU_MAX_SCANOUTS];
}GPU_RESP_DISP_INFO, *PGPU_RESP_DISP_INFO;
#pragma pack()

#pragma pack(1)
typedef struct virtio_gpu_object {
    UINT hw_res_handle;
    VirtIOBufferDescriptor* pages;
    PVOID vmap;
    BOOLEAN dumb;
}GPU_OBJECT, *PGPU_OBJECT;
#pragma pack()

#pragma pack(1)
typedef struct virtio_gpu_display_mode {
    USHORT XResolution;
    USHORT YResolution;
    USHORT Bits;
}GPU_DISP_MODE, *PGPU_DISP_MODE;
#pragma pack()

#pragma pack(1)
typedef struct virtio_gpu_cursor_pos {
    ULONG scanout_id;
    ULONG x;
    ULONG y;
    ULONG padding;
}GPU_CURSOR_POS, *PGPU_CURSOR_POS;
#pragma pack()

/* VIRTIO_GPU_CMD_UPDATE_CURSOR, VIRTIO_GPU_CMD_MOVE_CURSOR */
#pragma pack(1)
typedef struct virtio_gpu_update_cursor {
    GPU_CTRL_HDR hdr;
    GPU_CURSOR_POS pos;  /* update & move */
    ULONG resource_id;  /* update only */
    ULONG hot_x;        /* update only */
    ULONG hot_y;        /* update only */
    ULONG padding;
}GPU_UPDATE_CURSOR, *PGPU_UPDATE_CURSOR;
#pragma pack()

#define ISR_REASON_DISPLAY 1
#define ISR_REASON_CURSOR  2
#define ISR_REASON_CHANGE  4