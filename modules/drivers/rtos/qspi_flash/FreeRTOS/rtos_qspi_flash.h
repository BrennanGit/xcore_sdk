// Copyright (c) 2020, XMOS Ltd, All rights reserved

#ifndef RTOS_QSPI_FLASH_H_
#define RTOS_QSPI_FLASH_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "qspi_flash.h"

#include "drivers/rtos/rpc/api/rtos_driver_rpc.h"

typedef struct rtos_qspi_flash_struct rtos_qspi_flash_t;

struct rtos_qspi_flash_struct {
    rtos_driver_rpc_t *rpc_config;

    __attribute__((fptrgroup("rtos_qspi_flash_read_fptr_grp")))
    void (*read)(rtos_qspi_flash_t *, uint8_t *, unsigned, size_t);

    __attribute__((fptrgroup("rtos_qspi_flash_write_fptr_grp")))
    void (*write)(rtos_qspi_flash_t *, const uint8_t *, unsigned, size_t);

    __attribute__((fptrgroup("rtos_qspi_flash_erase_fptr_grp")))
    void (*erase)(rtos_qspi_flash_t *, unsigned, size_t);

    __attribute__((fptrgroup("rtos_qspi_flash_lock_fptr_grp")))
    void (*lock)(rtos_qspi_flash_t *);

    __attribute__((fptrgroup("rtos_qspi_flash_unlock_fptr_grp")))
    void (*unlock)(rtos_qspi_flash_t *);

    qspi_flash_ctx_t ctx;

    uint32_t quad_enable_register_read_cmd;
    uint32_t quad_enable_register_write_cmd;
    uint32_t quad_enable_bitmask;
    size_t page_size;
    size_t flash_size;
    uint32_t page_address_mask;

    unsigned op_task_priority;
    /* BEGIN RTOS SPECIFIC MEMBERS. */
    TaskHandle_t op_task;
    QueueHandle_t op_queue;
    SemaphoreHandle_t mutex;
};

#include "drivers/rtos/qspi_flash/api/rtos_qspi_flash_rpc.h"

inline void rtos_qspi_flash_lock(
        rtos_qspi_flash_t *ctx)
{
    ctx->lock(ctx);
}

inline void rtos_qspi_flash_unlock(
        rtos_qspi_flash_t *ctx)
{
    ctx->unlock(ctx);
}

inline void rtos_qspi_flash_read(
        rtos_qspi_flash_t *ctx,
        uint8_t *data,
        unsigned address,
        size_t len)
{
    ctx->read(ctx, data, address, len);
}

inline void rtos_qspi_flash_write(
        rtos_qspi_flash_t *ctx,
        const uint8_t *data,
        unsigned address,
        size_t len)
{
    ctx->write(ctx, data, address, len);
}

inline void rtos_qspi_flash_erase(
        rtos_qspi_flash_t *ctx,
        unsigned address,
        size_t len)
{
    ctx->erase(ctx, address, len);
}

inline size_t rtos_qspi_flash_size_get(
        rtos_qspi_flash_t *qspi_flash_ctx)
{
    return qspi_flash_ctx->flash_size;
}

void rtos_qspi_flash_start(
        rtos_qspi_flash_t *qspi_flash_ctx,
        unsigned priority);

void rtos_qspi_flash_init(
        rtos_qspi_flash_t *ctx,
        xclock_t clock_block,
        port_t cs_port,
        port_t sclk_port,
        port_t sio_port,
        int source_clock,
        int full_speed_clk_divisor,
        uint32_t full_speed_sclk_sample_delay,
        qspi_io_sample_edge_t full_speed_sclk_sample_edge,
        uint32_t full_speed_sio_pad_delay,
        int spi_read_clk_divisor,
        uint32_t spi_read_sclk_sample_delay,
        qspi_io_sample_edge_t spi_read_sclk_sample_edge,
        uint32_t spi_read_sio_pad_delay,
        int quad_page_program_enable,
        uint32_t quad_page_program_cmd,
        uint32_t quad_enable_register_read_cmd,
        uint32_t quad_enable_register_write_cmd,
        uint32_t quad_enable_bitmask,
        size_t page_size,
        size_t page_count);


#endif /* RTOS_QSPI_FLASH_H_ */
