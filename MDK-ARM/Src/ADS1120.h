#ifndef ADS1120_H
#define ADS1120_H

/**
 * @file ADS1120.h
 * @author xfp23 @github.com/xfp23
 * @brief ADS1120 library
 * @version 0.2
 * @date 2024-12-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "main.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

// 命令字节:
#define ADS1120_RESET (uint8_t)0X06      // 复位命令
#define ADS1120_RDATA (uint8_t)0x10      // 读数据命令
#define ADS1120_START_SYNC (uint8_t)0x08 // 启动转换
#define ADS1120_POWERDOWN (uint8_t)0x02  // 掉电模式
#define ADS1120_RREG (uint8_t)0X20       // 读寄存器命令
#define ADS1120_WREG (uint8_t)0x40       // 写寄存器命令
#define ADS1120_RREG_ALL (uint8_t)0x23   // 读回全部寄存器的值

/**
 * @brief 寄存器地址
 * @note 单字节
 */
#define REG0_WREG (uint8_t)0x40 // 写寄存器0地址
#define REG0_RREG (uint8_t)0x20 // 读寄存器0地址
#define REG1_WREG (uint8_t)0x44 // 写寄存器1地址
#define REG1_RREG (uint8_t)0X24 // 读寄存器1地址
#define REG2_WREG (uint8_t)0x48 // 写寄存器2地址
#define REG2_RREG (uint8_t)0x28 // 读寄存器2地址
#define REG3_WREG (uint8_t)0x4c // 写寄存器3地址
#define REG3_RREG (uint8_t)0x2c // 读寄存器3地址

#define ADS1120_OK 0x00
#define ADS1120_ERROR 0xff
#define ADS1120_TIMEOUT 100 // spi通信超时时间 ms

#define ADS1120_CS_LOW(ADS1120) HAL_GPIO_WritePin(ADS1120->config.Hareware.ADS1120_CS_Port, ADS1120->config.Hareware.ADS1120_CS_Pin, GPIO_PIN_RESET) // 拉低片选
#define ADS1120_CS_HIGH(ADS1120) HAL_GPIO_WritePin(ADS1120->config.Hareware.ADS1120_CS_Port, ADS1120->config.Hareware.ADS1120_CS_Pin, GPIO_PIN_SET)  // 拉高片选

/**
 * @brief 此处是寄存器0的控制命令字节
 */

/**
 * @brief 输入多路复用器配置宏
 */
#define MUX_AIN0_AIN1 (uint8_t)(0x00) // AINP = AIN0, AINN = AIN1（默认值）
#define MUX_AIN0_AIN2 (uint8_t)(0x01) // AINP = AIN0, AINN = AIN2
#define MUX_AIN0_AIN3 (uint8_t)(0x02) // AINP = AIN0, AINN = AIN3
#define MUX_AIN1_AIN2 (uint8_t)(0x03) // AINP = AIN1, AINN = AIN2
#define MUX_AIN1_AIN3 (uint8_t)(0x04) // AINP = AIN1, AINN = AIN3
#define MUX_AIN2_AIN3 (uint8_t)(0x05) // AINP = AIN2, AINN = AIN3
#define MUX_AIN1_AIN0 (uint8_t)(0x06) // AINP = AIN1, AINN = AIN0
#define MUX_AIN3_AIN2 (uint8_t)(0x07) // AINP = AIN3, AINN = AIN2
#define MUX_AIN0_AVSS (uint8_t)(0x08) // AINP = AIN0, AINN = AVSS
#define MUX_AIN1_AVSS (uint8_t)(0x09) // AINP = AIN1, AINN = AVSS
#define MUX_AIN2_AVSS (uint8_t)(0x0A) // AINP = AIN2, AINN = AVSS
#define MUX_AIN3_AVSS (uint8_t)(0x0B) // AINP = AIN3, AINN = AVSS
#define MUX_VREF_MONITOR_1 (0x0C)     // (V(REFPx) – V(REFNx)) / 4 监控（PGA旁路）
#define MUX_AVDD_MONITOR (0x0D)       // (AVDD – AVSS) / 4 监控（PGA旁路）
#define MUX_SHORTED_VCM (0x0E)        // AINP 和 AINN 短接到 (AVDD + AVSS) / 2
#define MUX_RESERVED (0x0F)           // 保留

/**
 * @brief 增益配置宏
 */
#define GAIN_1X (uint8_t)(0x00)   // 增益 = 1（默认值）
#define GAIN_2X (uint8_t)(0x01)   // 增益 = 2
#define GAIN_4X (uint8_t)(0x02)   // 增益 = 4
#define GAIN_8X (uint8_t)(0x03)   // 增益 = 8
#define GAIN_16X (uint8_t)(0x04)  // 增益 = 16
#define GAIN_32X (uint8_t)(0x05)  // 增益 = 32
#define GAIN_64X (uint8_t)(0x06)  // 增益 = 64
#define GAIN_128X (uint8_t)(0x07) // 增益 = 128

/**
 * @brief PGA旁路配置宏
 */
#define PGA_ENABLED (uint8_t)0x00  // PGA启用（默认值）
#define PGA_DISABLED (uint8_t)0x01 // PGA禁用并旁路

/**
 * @brief 此处是寄存器1的控制命令字节
 */

// 电流源设置
#define CURRENT_SOURCE_ENABLED (uint8_t)0x01  // 启用电流源
#define CURRENT_SOURCE_DISABLED (uint8_t)0x00 // 禁用电流源

// 温度传感器设置
#define TEM_SENSOR_ENABLED (uint8_t)(0x01)  // 启用内部温度传感器（配置寄存器 0 的设置不起作用）
#define TEM_SENSOR_DISABLED (uint8_t)(0x00) // 禁用内部温度传感器

// 转换模式设置
#define SINGLE_SHOT_MODE (uint8_t)(0x00)           // 单次转换模式
#define CONTINUOUS_CONVERSION_MODE (uint8_t)(0x01) // 连续转换模式

// 工作模式设置
#define NORMAL_MODE (uint8_t)(0x00)     // 正常模式（256-kHz 调制器时钟，默认）
#define DUTY_CYCLE_MODE (uint8_t)(0x01) // 占空比模式（内部占空比为 1：4）
#define TURBO_MODE (uint8_t)(0x02)      // Turbo mode (512-kHz modulator clock)
#define RESERVED_MODE (uint8_t)(0x03)   // 保留模式

// 转换传输速度
#define DATA_RATE_1x 0
#define DATA_RATE_2x (0x01)
#define DATA_RATE_3x (0x02)
#define DATA_RATE_4x (0x03)
#define DATA_RATE_5x (0x04)
#define DATA_RATE_6x (0x05)
#define DATA_RATE_7x (0x06)
#define DATA_RATE_8x (0x07)

/**
 * @brief 此处是寄存器2的控制命令字节
 */

// 设置激励电流
#define EXCITATION_CURRENT_OFF (uint8_t)(0x00)
#define EXCITATION_CURRENT_50UA (uint8_t)(0X02)
#define EXCITATION_CURRENT_100UA (uint8_t)(0X03)
#define EXCITATION_CURRENT_250UA (uint8_t)(0X04)
#define EXCITATION_CURRENT_500UA (uint8_t)(0X05)
#define EXCITATION_CURRENT_1000UA (uint8_t)(0X06)
#define EXCITATION_CURRENT_1500UA (uint8_t)(0X07)

// 低侧电源开关配置
// 该位配置连接在 AIN3/REFN1 和 AVSS 之间的低侧开关的行为
#define LOW_SIDEPOWER_SWITCH_ON (0x01)
#define LOW_SIDEPOWER_SWITCH_OFF (0x00)

//	FIR filter configuration
// 这些位配置内部 FIR 滤波器的滤波器系数
// 仅将这些位与正常模式下的 20-SPS 设置和占空比模式下的 5-SPS 设置一起使用。对于所有其他数据速率，设置为 00
#define REJECTION_DISABLE (0X00)
#define REJECTION_50_60_HZ (0x01) // 同时实现50 60 hz 的抑制
#define REJECTION_50_HZ (0X02)    // 50HZ 的抑制
#define REJECTION_60_HZ (0x03)    // 60HZ 的抑制

// 基准电压源选择
// 这些位选择用于转换的基准电压源
#define VOL_2_048 (0X00)             // 已选择内部 2.048-V 基准电压源（默认）
#define REFP0_REFN0 (0X01)           // 使用专用 REFP0 和 REFN0 输入选择外部参考
#define AIN0_REFP1_AIN3_REFN1 (0X02) // 使用 AIN0/REFP1 和 AIN3/REFN1 输入选择外部参考
#define ANALOG_SUPPLY (0X03)         // 用作基准的模拟电源 (AVDD - AVSS)

    /**
     * @brief 此处是寄存器3的控制命令字节
     */

#define REG3_REVICE 0X00 // 第一位保留，always 0

#define DRDY_ONLY (0X00) // 当新数据准备就绪时，该位控制 DOUT/DRDY 引脚的行为。
#define DRDY_DOUT (0x01) // 在 DOUT/DRDY 和 DRDY 上同时指示数据就绪

// IDAC2 路由配置 这些位选择 IDAC2 路由到的通道。
#define IDCA2_DISABLE (0X00)
#define IDCA2_AIN0_REFP1 (0X01) // IDCA2连接到REFP1
#define IDCA2_AIN1 (0X02)       // IDC2连接到AIN1 下方注释以此类推
#define IDCA2_AIN2 (0X03)
#define IDCA2_AIN3_REFP1 (0X04)
#define IDCA2_REFP0 (0X05)
#define IDCA2_REFN0 (0X06)

// 这些位选择 IDAC1 路由到的通道
#define IDCA1_DISABLE (0X00)
#define IDCA1_AIN0_REFP1 (0X01) // IDCA1连接到 AIN0/REFP1
#define IDCA1_AIN1 (0x02)
#define IDCA1_AIN2 (0x03)
#define IDCA1_AIN3_REFN1 (0x04)
#define IDCA1_REFP0 (0X05)
#define IDCA1_REFN0 (0X06)
#define IDCA1_RESERVE (0X07)

    /**
     * @brief 类型
     *
     */
    __packed typedef struct
    {
        __packed struct
        {
            uint8_t PGA : 1;  // 配置PGA
            uint8_t GAIN : 3; // 选择增益
            uint8_t MUX : 4;  // 选择通道
        } REG0;

        __packed struct
        {
            uint8_t CURRENT_SOURCE : 1; // 电流源设置
            uint8_t TEM_SENSOR : 1;     // 内部温度传感器设置
            uint8_t CONVER_MODE : 1;    // 转换模式设置
            uint8_t WORK_MODE : 2;      // 工作模式设置
            uint8_t DATA_RATE : 3;      // 数据速率设置
        } REG1;

        __packed struct
        {
            uint8_t EXCITATION_CURRENT : 3;   // 设置激励电流
            uint8_t LOW_SIDEPOWER_SWITCH : 1; // 设置低侧开关
            uint8_t REJECTION : 2;            // 设置滤波系数
            uint8_t VREF : 2;                 // 设置参考电压
        } REG2;

        __packed struct
        {
            uint8_t Reserved_bit : 1; // 保留位
            uint8_t DRDY_ACT : 1;     // DRDY_ONLY/DRDY_DOUT 设置DRDY的行为
            uint8_t IDCA2 : 3;        // IDAC2 路由配置
            uint8_t IDCA1 : 3;        // IDAC1 路由配置
        } REG3;

    } ADS1120_Reg_t;

    typedef struct
    {
        GPIO_TypeDef *ADS1120_CS_Port;   // 片选引脚端口
        uint16_t ADS1120_CS_Pin;         // 片选引脚
        SPI_HandleTypeDef *ADS1120_hspi; // SPI句柄
    } ADS1120_Hareware_t;                // ADS1120硬件配置

    typedef struct
    {
        uint8_t DRDY_Signal; // DRDY中断信号
        bool READ_Flage;     // 读取标志
    } private;

    typedef struct
    {
        ADS1120_Reg_t Resgister;     // 寄存器配置
        ADS1120_Hareware_t Hareware; // 硬件配置

    } ADS1120_Conf_t;

    typedef struct
    {
        ADS1120_Conf_t config; // ADS1120配置
    private
        Signal; // 信号标志
    } ADS1120_Class_t;

// 配置面板
#define CONFIG_PANEL {                                                      \
    .config.Hareware.ADS1120_hspi = &hspi1,                                 \
    .config.Hareware.ADS1120_CS_Pin = GPIO_PIN_0,                           \
    .config.Hareware.ADS1120_CS_Port = GPIOB,                               \
    .config.Resgister.REG0.MUX = MUX_AIN0_AIN1,                             \
    .config.Resgister.REG0.GAIN = GAIN_1X,                                  \
    .config.Resgister.REG0.PGA = PGA_ENABLED,                               \
    .config.Resgister.REG1.CONVER_MODE = SINGLE_SHOT_MODE,                  \
    .config.Resgister.REG1.CURRENT_SOURCE = CURRENT_SOURCE_ENABLED,         \
    .config.Resgister.REG1.DATA_RATE = DATA_RATE_1x,                        \
    .config.Resgister.REG1.TEM_SENSOR = TEM_SENSOR_DISABLED,                \
    .config.Resgister.REG1.WORK_MODE = NORMAL_MODE,                         \
    .config.Resgister.REG2.EXCITATION_CURRENT = EXCITATION_CURRENT_500UA,   \
    .config.Resgister.REG2.LOW_SIDEPOWER_SWITCH = LOW_SIDEPOWER_SWITCH_OFF, \
    .config.Resgister.REG2.REJECTION = REJECTION_DISABLE,                   \
    .config.Resgister.REG2.VREF = VOL_2_048,                                \
    .config.Resgister.REG3.Reserved_bit = REG3_REVICE,                      \
    .config.Resgister.REG3.DRDY_ACT = DRDY_ONLY,                            \
    .config.Resgister.REG3.IDCA1 = IDCA1_DISABLE,                           \
    .config.Resgister.REG3.IDCA2 = IDCA2_DISABLE,                           \
}

    extern uint32_t ADS1120_Init(volatile ADS1120_Class_t *ADS1120);
    extern void ADS1120_Callback(volatile ADS1120_Class_t *ADS1120);
    extern uint16_t ADS1120_ContinuousRead(volatile ADS1120_Class_t *ADS1120);
    extern void ADS1120_SetChannel(volatile ADS1120_Class_t *ADS1120, uint8_t channel);
    extern uint8_t ADS1120_Check(volatile ADS1120_Class_t *ADS1120);
    extern uint16_t ADS1120_SignalRead(volatile ADS1120_Class_t *ADS1120);
#ifdef __cplusplus
}
#endif

#endif // ADS1120_H
