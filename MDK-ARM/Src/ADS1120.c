#include "spi.h"
#include "ADS1120.h"
#include <string.h>
static void WRDATA(volatile ADS1120_Class_t *ADS1120, uint8_t data)
{
    uint8_t byte = data;
    HAL_SPI_Transmit(ADS1120->config.Hareware.ADS1120_hspi, &byte, 1, ADS1120_TIMEOUT);
}

/**
 * @brief 初始化ADS1120
 * @note 请初始化ADS1120的config成员再传参数
 * @param ADS1120 对象
 *
 *
 * @return uint32_t ADS1120寄存器配置结果
 */
uint32_t ADS1120_Init(volatile ADS1120_Class_t *ADS1120)
{
    uint8_t byte[4] = {0};
    uint8_t read[4] = {0};
    uint32_t reg = 0;
    ADS1120_CS_HIGH(ADS1120);
    HAL_Delay(1);
    ADS1120_CS_LOW(ADS1120);
    memcpy((void *)byte, (const void *)&ADS1120->config.Resgister, 4);
    WRDATA(ADS1120, ADS1120_RESET); // 复位ADS1120
    WRDATA(ADS1120, REG0_WREG);
    WRDATA(ADS1120, byte[0]);
    WRDATA(ADS1120, REG1_WREG);
    WRDATA(ADS1120, byte[1]);
    WRDATA(ADS1120, REG2_WREG);
    WRDATA(ADS1120, byte[2]);
    WRDATA(ADS1120, REG3_WREG);
    WRDATA(ADS1120, byte[3]);
    HAL_Delay(100);
    WRDATA(ADS1120, ADS1120_RREG_ALL);
    HAL_SPI_Receive(ADS1120->config.Hareware.ADS1120_hspi, read, 4, ADS1120_TIMEOUT);
    reg = (read[0] << 24) | (read[1] << 16) | (read[2] << 8) | read[3];
    WRDATA(ADS1120, ADS1120_START_SYNC);
    return reg;
}

/**
 * @brief ADS1120中断回调函数
 * @note 将此函数放在DRDY引脚的外部中断函数中，中断类型: 双边沿触发
 * @param ADS1120对象
 */
void ADS1120_Callback(volatile ADS1120_Class_t *ADS1120)
{
    ADS1120->Signal.DRDY_Signal++;
    switch (ADS1120->config.Resgister.REG1.CONVER_MODE)
    {
    case SINGLE_SHOT_MODE:
        if (ADS1120->Signal.DRDY_Signal == 1)
        {
            ADS1120->Signal.READ_Flage = true;
        }
        else if (ADS1120->Signal.DRDY_Signal >= 2)
        {
            ADS1120->Signal.DRDY_Signal = 0;
        }
        break;
    case CONTINUOUS_CONVERSION_MODE:
        if (ADS1120->Signal.DRDY_Signal == 3)
        {
            ADS1120->Signal.READ_Flage = true; // 开始读取数据
        }
        else if (ADS1120->Signal.DRDY_Signal == 4)
        {
            ADS1120->Signal.DRDY_Signal = 0;
        }
        break;
    }
}

/**
 * @brief 读取ADS1120在连续转换模式下的转换结果
 *
 * @param ADS1120 对象
 * @return uint16_t 转换结果
 */
uint16_t ADS1120_ContinuousRead(volatile ADS1120_Class_t *ADS1120)
{

    // HAL_GPIO_WritePin(ADS1120->config.Hareware.ADS1120_CS_Port,ADS1120->config.Hareware.ADS1120_CS_Pin,GPIO_PIN_RESET); // 拉低片选

    uint8_t data[2] = {0};
    ADS1120->Signal.READ_Flage = false;
    HAL_SPI_Receive(ADS1120->config.Hareware.ADS1120_hspi, data, 2, ADS1120_TIMEOUT);
    return (uint16_t)(data[0] << 8) | data[1];
}

/**
 * @brief ADS1120切换通道
 *
 * @param ADS1120对象
 * @param channel 通道号
 */
void ADS1120_SetChannel(volatile ADS1120_Class_t *ADS1120, uint8_t channel)
{
    uint8_t data[3] = {0};
    data[0] = REG0_WREG;
    memcpy(&data[1], (const void *)&ADS1120->config.Resgister.REG0, 1);

    data[1] &= 0x0f;
    data[1] |= channel;
    data[2] = 0; // 为了补全时序

    HAL_SPI_Transmit(ADS1120->config.Hareware.ADS1120_hspi, data, 3, ADS1120_TIMEOUT);
}

/**
 * @brief 检查ADS1120数据是否就绪
 * @note 只有在ADS1120_Check返回ADS1120_OK时调用ADS1120读取转换结果API才有效
 * @param ADS1120
 * @return ADS1120_OK or ADS1120_ERROR
 */
uint8_t ADS1120_Check(volatile ADS1120_Class_t *ADS1120)
{
    if (ADS1120->Signal.READ_Flage == true)
    {
        return ADS1120_OK;
    }
    return ADS1120_ERROR;
}

/**
 * @brief 单次转换模式下读取转换结果
 *
 * @param ADS1120
 * @return ADC值
 */
uint16_t ADS1120_SignalRead(volatile ADS1120_Class_t *ADS1120)
{
    uint8_t data[3] = {0};
    uint16_t result = 0;
    ADS1120->Signal.READ_Flage = false;
    WRDATA(ADS1120, ADS1120_RDATA);
    HAL_SPI_Receive(ADS1120->config.Hareware.ADS1120_hspi, data, 3, ADS1120_TIMEOUT);
    result = (uint16_t)(data[1] << 8) | data[2];
    return result;
}
