/**
 * @file i8080_test.c
 * @author Product Application Department
 * @brief  I8080 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup I8080 I8080模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "i8080_test.h"
#include "pinswap_drv.h"
#include "axidma_test.h"
#include "cpm_hal.h"
// 全局变量定义
lcd_dev_t lcddev;
#define writew(addr, value) (*(volatile unsigned short *)(addr)) = ((unsigned short)(value))
// 函数定义

/**
 * @brief I8080 模块写寄存器函数
 *
 * @param regval 寄存器值
 */
void LCD_WR_REG(volatile uint16_t regval)
{
    regval = regval;           // 使用-O2优化的时候,必须插入的延时
    MCU_LCD->LCD_REG = regval; // 写入要写的寄存器序号
}

/**
 * @brief I8080 模块写LCD数据函数
 *
 * @param data 要写入的值
 */
void LCD_WR_DATA(volatile uint16_t data)
{
    data = data; // 使用-O2优化的时候,必须插入的延时
    MCU_LCD->LCD_RAM = data;
}

/**
 * @brief I8080 模块读LCD数据函数
 *
 * @return uint16_t 读到的值
 */
uint16_t LCD_RD_DATA(void)
{
    volatile uint16_t ram; // 防止被优化
    ram = MCU_LCD->LCD_RAM;
    return ram;
}

/**
 * @brief I8080 模块写寄存器函数
 *
 * @param LCD_Reg 寄存器地址
 * @param LCD_RegValue 要写入的数据
 */
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
    MCU_LCD->LCD_REG = LCD_Reg;      // 写入要写的寄存器序号
    MCU_LCD->LCD_RAM = LCD_RegValue; // 写入数据
}

/**
 * @brief I8080 模块读寄存器函数
 *
 * @param LCD_Reg 寄存器地址
 * @return uint16_t 读到的数据
 */
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
    LCD_WR_REG(LCD_Reg); // 写入要读的寄存器序号
    delay(500);
    return LCD_RD_DATA(); // 返回读到的值
}

/**
 * @brief I8080 模块设置光标位置函数
 *
 * @param Xpos 横坐标
 * @param Ypos 纵坐标
 */
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(Xpos >> 8);
    LCD_WR_REG(lcddev.setxcmd + 1);
    LCD_WR_DATA(Xpos & 0XFF);
    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(Ypos >> 8);
    LCD_WR_REG(lcddev.setycmd + 1);
    LCD_WR_DATA(Ypos & 0XFF);
}
/**
 * @brief I8080 模块准备开始刷图函数
 *
 */
void LCD_WriteRAM_Prepare(void)
{
    MCU_LCD->LCD_REG = lcddev.wramcmd;
}

/**
 * @brief I8080 模块设置窗口,并自动设置画点坐标到窗口左上角(sx,sy)函数
 *
 * @param sx 窗口起始x坐标
 * @param sy 窗口起始y坐标
 * @param width 窗口宽度
 * @param height 窗口高度
 */
void LCD_Set_Window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    uint16_t twidth, theight;
    twidth = sx + width - 1;
    theight = sy + height - 1;

    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(sx >> 8);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(sx & 0XFF);
        LCD_WR_REG(lcddev.setxcmd + 2);
        LCD_WR_DATA(twidth >> 8);
        LCD_WR_REG(lcddev.setxcmd + 3);
        LCD_WR_DATA(twidth & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(sy >> 8);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(sy & 0XFF);
        LCD_WR_REG(lcddev.setycmd + 2);
        LCD_WR_DATA(theight >> 8);
        LCD_WR_REG(lcddev.setycmd + 3);
        LCD_WR_DATA(theight & 0XFF);
    }
}

/**
 * @brief I8080 模块设置LCD的自动扫描方向函数
 *
 * @param dir :0~7,代表8个方向
 * @return * void
 */
void LCD_Scan_Dir(uint8_t dir)
{
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;
    if ((lcddev.dir == 1 && lcddev.id != 0X1963) || (lcddev.dir == 0 && lcddev.id == 0X1963)) // 横屏时，对1963不改变扫描方向！竖屏时1963改变方向
    {
        switch (dir) // 方向转换
        {
        case 0:
            dir = 6;
            break;
        case 1:
            dir = 7;
            break;
        case 2:
            dir = 4;
            break;
        case 3:
            dir = 5;
            break;
        case 4:
            dir = 1;
            break;
        case 5:
            dir = 0;
            break;
        case 6:
            dir = 3;
            break;
        case 7:
            dir = 2;
            break;
        }
    }
    if (lcddev.id == 0x9341 || lcddev.id == 0X5310 || lcddev.id == 0X5510 || lcddev.id == 0X1963) // 9341/5310/5510/1963,特殊处理
    {
        switch (dir)
        {
        case L2R_U2D: // 从左到右,从上到下
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;
        case L2R_D2U: // 从左到右,从下到上
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;
        case R2L_U2D: // 从右到左,从上到下
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;
        case R2L_D2U: // 从右到左,从下到上
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;
        case U2D_L2R: // 从上到下,从左到右
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;
        case U2D_R2L: // 从上到下,从右到左
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;
        case D2U_L2R: // 从下到上,从左到右
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;
        case D2U_R2L: // 从下到上,从右到左
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
        }
        if (lcddev.id == 0X5510)
            dirreg = 0X3600;
        else
            dirreg = 0X36;
        if ((lcddev.id != 0X5310) && (lcddev.id != 0X5510) && (lcddev.id != 0X1963))
            regval |= 0X08; // 5310/5510/1963不需要BGR
        LCD_WriteReg(dirreg, regval);
        if (lcddev.id != 0X1963) // 1963不做坐标处理
        {
            if (regval & 0X20)
            {
                if (lcddev.width < lcddev.height) // 交换X,Y
                {
                    temp = lcddev.width;
                    lcddev.width = lcddev.height;
                    lcddev.height = temp;
                }
            }
            else
            {
                if (lcddev.width > lcddev.height) // 交换X,Y
                {
                    temp = lcddev.width;
                    lcddev.width = lcddev.height;
                    lcddev.height = temp;
                }
            }
        }
        if (lcddev.id == 0X5510)
        {
            LCD_WR_REG(lcddev.setxcmd);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setxcmd + 1);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setxcmd + 2);
            LCD_WR_DATA((lcddev.width - 1) >> 8);
            LCD_WR_REG(lcddev.setxcmd + 3);
            LCD_WR_DATA((lcddev.width - 1) & 0XFF);
            LCD_WR_REG(lcddev.setycmd);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setycmd + 1);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setycmd + 2);
            LCD_WR_DATA((lcddev.height - 1) >> 8);
            LCD_WR_REG(lcddev.setycmd + 3);
            LCD_WR_DATA((lcddev.height - 1) & 0XFF);
        }
        else
        {
            LCD_WR_REG(lcddev.setxcmd);
            LCD_WR_DATA(0);
            LCD_WR_DATA(0);
            LCD_WR_DATA((lcddev.width - 1) >> 8);
            LCD_WR_DATA((lcddev.width - 1) & 0XFF);
            LCD_WR_REG(lcddev.setycmd);
            LCD_WR_DATA(0);
            LCD_WR_DATA(0);
            LCD_WR_DATA((lcddev.height - 1) >> 8);
            LCD_WR_DATA((lcddev.height - 1) & 0XFF);
        }
    }
}

/**
 * @brief I8080B 模块设置LCD显示方向函数
 *
 * @param dir 0,竖屏；1,横屏
 */
void LCD_Display_Dir(uint8_t dir)
{
    lcddev.dir = dir; // 竖屏/横屏
    if (dir == 0)     // 竖屏
    {
        lcddev.width = 240;
        lcddev.height = 320;
        if (lcddev.id == 0X9341 || lcddev.id == 0X5310)
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
            if (lcddev.id == 0X5310)
            {
                lcddev.width = 320;
                lcddev.height = 480;
            }
        }
        else if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;
            lcddev.setxcmd = 0X2A00;
            lcddev.setycmd = 0X2B00;
            lcddev.width = 480;
            lcddev.height = 800;
        }
        else if (lcddev.id == 0X1963)
        {
            lcddev.wramcmd = 0X2C; // 设置写入GRAM的指令
            lcddev.setxcmd = 0X2B; // 设置写X坐标指令
            lcddev.setycmd = 0X2A; // 设置写Y坐标指令
            lcddev.width = 480;    // 设置宽度480
            lcddev.height = 800;   // 设置高度800
        }
    }
    else // 横屏
    {
        lcddev.width = 320;
        lcddev.height = 240;
        if (lcddev.id == 0X9341 || lcddev.id == 0X5310)
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }
        else if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;
            lcddev.setxcmd = 0X2A00;
            lcddev.setycmd = 0X2B00;
            lcddev.width = 800;
            lcddev.height = 480;
        }
        else if (lcddev.id == 0X1963)
        {
            lcddev.wramcmd = 0X2C; // 设置写入GRAM的指令
            lcddev.setxcmd = 0X2A; // 设置写X坐标指令
            lcddev.setycmd = 0X2B; // 设置写Y坐标指令
            lcddev.width = 800;    // 设置宽度800
            lcddev.height = 480;   // 设置高度480
        }
        if (lcddev.id == 0X5310)
        {
            lcddev.width = 480;
            lcddev.height = 320;
        }
    }
    LCD_Scan_Dir(DFT_SCAN_DIR); // 默认扫描方向
}

/**
 * @brief I8080 模块清屏函数
 *
 * @param color 要清屏的填充色
 */
void LCD_Clear(uint32_t color)
{
    uint32_t index = 0;
    uint32_t totalpoint = lcddev.width;
    totalpoint *= lcddev.height; // 得到总点数
    LCD_SetCursor(0x00, 0x0000); // 设置光标位置
    LCD_WriteRAM_Prepare();      // 开始写入GRAM
    for (index = 0; index < totalpoint; index++)
    {
        MCU_LCD->LCD_RAM = color;
    }
}

/**
 * @brief I8080 模块LCD写GRAM函数
 *
 * @param RGB_Code 颜色值
 */
void LCD_WriteRAM(uint16_t RGB_Code)
{
    MCU_LCD->LCD_RAM = RGB_Code; // 写十六位GRAM
}

/**
 * @brief I8080 模块初始化屏幕函数
 *
 */
void mcu_lcd_init(void)
{
    uint32_t id;
    uint32_t i, j;
    uint16_t tmp;
    uint16_t color[480];

    lcddev.id = 0X5510;

    LCD_WR_REG(0XDA00);
    id = LCD_RD_DATA(); // 读回0X00
    LCD_WR_REG(0XDB00);
    id = LCD_RD_DATA(); // 读回0X80
    id <<= 8;
    LCD_WR_REG(0XDC00);
    id |= LCD_RD_DATA(); // 读回0X00
    printf("LCD ID = 0x%X\r\n", id);

    lcddev.id = 0x5510; // NT35510读回的ID是8000H,为方便区分,我们强制设置为5510
    LCD_Display_Dir(1); // 1-横屏显示, 0-竖屏显示

    LCD_WriteReg(0xF000, 0x55);
    LCD_WriteReg(0xF001, 0xAA);
    LCD_WriteReg(0xF002, 0x52);
    LCD_WriteReg(0xF003, 0x08);
    LCD_WriteReg(0xF004, 0x01);
    // AVDD Set AVDD 5.2V
    LCD_WriteReg(0xB000, 0x0D);
    LCD_WriteReg(0xB001, 0x0D);
    LCD_WriteReg(0xB002, 0x0D);
    // AVDD ratio
    LCD_WriteReg(0xB600, 0x34);
    LCD_WriteReg(0xB601, 0x34);
    LCD_WriteReg(0xB602, 0x34);
    // AVEE -5.2V
    LCD_WriteReg(0xB100, 0x0D);
    LCD_WriteReg(0xB101, 0x0D);
    LCD_WriteReg(0xB102, 0x0D);
    // AVEE ratio
    LCD_WriteReg(0xB700, 0x34);
    LCD_WriteReg(0xB701, 0x34);
    LCD_WriteReg(0xB702, 0x34);
    // VCL -2.5V
    LCD_WriteReg(0xB200, 0x00);
    LCD_WriteReg(0xB201, 0x00);
    LCD_WriteReg(0xB202, 0x00);
    // VCL ratio
    LCD_WriteReg(0xB800, 0x24);
    LCD_WriteReg(0xB801, 0x24);
    LCD_WriteReg(0xB802, 0x24);
    // VGH 15V (Free pump)
    LCD_WriteReg(0xBF00, 0x01);
    LCD_WriteReg(0xB300, 0x0F);
    LCD_WriteReg(0xB301, 0x0F);
    LCD_WriteReg(0xB302, 0x0F);
    // VGH ratio
    LCD_WriteReg(0xB900, 0x34);
    LCD_WriteReg(0xB901, 0x34);
    LCD_WriteReg(0xB902, 0x34);
    // VGL_REG -10V
    LCD_WriteReg(0xB500, 0x08);
    LCD_WriteReg(0xB501, 0x08);
    LCD_WriteReg(0xB502, 0x08);
    LCD_WriteReg(0xC200, 0x03);
    // VGLX ratio
    LCD_WriteReg(0xBA00, 0x24);
    LCD_WriteReg(0xBA01, 0x24);
    LCD_WriteReg(0xBA02, 0x24);
    // VGMP/VGSP 4.5V/0V
    LCD_WriteReg(0xBC00, 0x00);
    LCD_WriteReg(0xBC01, 0x78);
    LCD_WriteReg(0xBC02, 0x00);
    // VGMN/VGSN -4.5V/0V
    LCD_WriteReg(0xBD00, 0x00);
    LCD_WriteReg(0xBD01, 0x78);
    LCD_WriteReg(0xBD02, 0x00);
    // VCOM
    LCD_WriteReg(0xBE00, 0x00);
    LCD_WriteReg(0xBE01, 0x64);
    // Gamma Setting
    LCD_WriteReg(0xD100, 0x00);
    LCD_WriteReg(0xD101, 0x33);
    LCD_WriteReg(0xD102, 0x00);
    LCD_WriteReg(0xD103, 0x34);
    LCD_WriteReg(0xD104, 0x00);
    LCD_WriteReg(0xD105, 0x3A);
    LCD_WriteReg(0xD106, 0x00);
    LCD_WriteReg(0xD107, 0x4A);
    LCD_WriteReg(0xD108, 0x00);
    LCD_WriteReg(0xD109, 0x5C);
    LCD_WriteReg(0xD10A, 0x00);
    LCD_WriteReg(0xD10B, 0x81);
    LCD_WriteReg(0xD10C, 0x00);
    LCD_WriteReg(0xD10D, 0xA6);
    LCD_WriteReg(0xD10E, 0x00);
    LCD_WriteReg(0xD10F, 0xE5);
    LCD_WriteReg(0xD110, 0x01);
    LCD_WriteReg(0xD111, 0x13);
    LCD_WriteReg(0xD112, 0x01);
    LCD_WriteReg(0xD113, 0x54);
    LCD_WriteReg(0xD114, 0x01);
    LCD_WriteReg(0xD115, 0x82);
    LCD_WriteReg(0xD116, 0x01);
    LCD_WriteReg(0xD117, 0xCA);
    LCD_WriteReg(0xD118, 0x02);
    LCD_WriteReg(0xD119, 0x00);
    LCD_WriteReg(0xD11A, 0x02);
    LCD_WriteReg(0xD11B, 0x01);
    LCD_WriteReg(0xD11C, 0x02);
    LCD_WriteReg(0xD11D, 0x34);
    LCD_WriteReg(0xD11E, 0x02);
    LCD_WriteReg(0xD11F, 0x67);
    LCD_WriteReg(0xD120, 0x02);
    LCD_WriteReg(0xD121, 0x84);
    LCD_WriteReg(0xD122, 0x02);
    LCD_WriteReg(0xD123, 0xA4);
    LCD_WriteReg(0xD124, 0x02);
    LCD_WriteReg(0xD125, 0xB7);
    LCD_WriteReg(0xD126, 0x02);
    LCD_WriteReg(0xD127, 0xCF);
    LCD_WriteReg(0xD128, 0x02);
    LCD_WriteReg(0xD129, 0xDE);
    LCD_WriteReg(0xD12A, 0x02);
    LCD_WriteReg(0xD12B, 0xF2);
    LCD_WriteReg(0xD12C, 0x02);
    LCD_WriteReg(0xD12D, 0xFE);
    LCD_WriteReg(0xD12E, 0x03);
    LCD_WriteReg(0xD12F, 0x10);
    LCD_WriteReg(0xD130, 0x03);
    LCD_WriteReg(0xD131, 0x33);
    LCD_WriteReg(0xD132, 0x03);
    LCD_WriteReg(0xD133, 0x6D);
    LCD_WriteReg(0xD200, 0x00);
    LCD_WriteReg(0xD201, 0x33);
    LCD_WriteReg(0xD202, 0x00);
    LCD_WriteReg(0xD203, 0x34);
    LCD_WriteReg(0xD204, 0x00);
    LCD_WriteReg(0xD205, 0x3A);
    LCD_WriteReg(0xD206, 0x00);
    LCD_WriteReg(0xD207, 0x4A);
    LCD_WriteReg(0xD208, 0x00);
    LCD_WriteReg(0xD209, 0x5C);
    LCD_WriteReg(0xD20A, 0x00);

    LCD_WriteReg(0xD20B, 0x81);
    LCD_WriteReg(0xD20C, 0x00);
    LCD_WriteReg(0xD20D, 0xA6);
    LCD_WriteReg(0xD20E, 0x00);
    LCD_WriteReg(0xD20F, 0xE5);
    LCD_WriteReg(0xD210, 0x01);
    LCD_WriteReg(0xD211, 0x13);
    LCD_WriteReg(0xD212, 0x01);
    LCD_WriteReg(0xD213, 0x54);
    LCD_WriteReg(0xD214, 0x01);
    LCD_WriteReg(0xD215, 0x82);
    LCD_WriteReg(0xD216, 0x01);
    LCD_WriteReg(0xD217, 0xCA);
    LCD_WriteReg(0xD218, 0x02);
    LCD_WriteReg(0xD219, 0x00);
    LCD_WriteReg(0xD21A, 0x02);
    LCD_WriteReg(0xD21B, 0x01);
    LCD_WriteReg(0xD21C, 0x02);
    LCD_WriteReg(0xD21D, 0x34);
    LCD_WriteReg(0xD21E, 0x02);
    LCD_WriteReg(0xD21F, 0x67);
    LCD_WriteReg(0xD220, 0x02);
    LCD_WriteReg(0xD221, 0x84);
    LCD_WriteReg(0xD222, 0x02);
    LCD_WriteReg(0xD223, 0xA4);
    LCD_WriteReg(0xD224, 0x02);
    LCD_WriteReg(0xD225, 0xB7);
    LCD_WriteReg(0xD226, 0x02);
    LCD_WriteReg(0xD227, 0xCF);
    LCD_WriteReg(0xD228, 0x02);
    LCD_WriteReg(0xD229, 0xDE);
    LCD_WriteReg(0xD22A, 0x02);
    LCD_WriteReg(0xD22B, 0xF2);
    LCD_WriteReg(0xD22C, 0x02);
    LCD_WriteReg(0xD22D, 0xFE);
    LCD_WriteReg(0xD22E, 0x03);
    LCD_WriteReg(0xD22F, 0x10);
    LCD_WriteReg(0xD230, 0x03);
    LCD_WriteReg(0xD231, 0x33);
    LCD_WriteReg(0xD232, 0x03);
    LCD_WriteReg(0xD233, 0x6D);
    LCD_WriteReg(0xD300, 0x00);
    LCD_WriteReg(0xD301, 0x33);
    LCD_WriteReg(0xD302, 0x00);
    LCD_WriteReg(0xD303, 0x34);
    LCD_WriteReg(0xD304, 0x00);
    LCD_WriteReg(0xD305, 0x3A);
    LCD_WriteReg(0xD306, 0x00);
    LCD_WriteReg(0xD307, 0x4A);
    LCD_WriteReg(0xD308, 0x00);
    LCD_WriteReg(0xD309, 0x5C);
    LCD_WriteReg(0xD30A, 0x00);

    LCD_WriteReg(0xD30B, 0x81);
    LCD_WriteReg(0xD30C, 0x00);
    LCD_WriteReg(0xD30D, 0xA6);
    LCD_WriteReg(0xD30E, 0x00);
    LCD_WriteReg(0xD30F, 0xE5);
    LCD_WriteReg(0xD310, 0x01);
    LCD_WriteReg(0xD311, 0x13);
    LCD_WriteReg(0xD312, 0x01);
    LCD_WriteReg(0xD313, 0x54);
    LCD_WriteReg(0xD314, 0x01);
    LCD_WriteReg(0xD315, 0x82);
    LCD_WriteReg(0xD316, 0x01);
    LCD_WriteReg(0xD317, 0xCA);
    LCD_WriteReg(0xD318, 0x02);
    LCD_WriteReg(0xD319, 0x00);
    LCD_WriteReg(0xD31A, 0x02);
    LCD_WriteReg(0xD31B, 0x01);
    LCD_WriteReg(0xD31C, 0x02);
    LCD_WriteReg(0xD31D, 0x34);
    LCD_WriteReg(0xD31E, 0x02);
    LCD_WriteReg(0xD31F, 0x67);
    LCD_WriteReg(0xD320, 0x02);
    LCD_WriteReg(0xD321, 0x84);
    LCD_WriteReg(0xD322, 0x02);
    LCD_WriteReg(0xD323, 0xA4);
    LCD_WriteReg(0xD324, 0x02);
    LCD_WriteReg(0xD325, 0xB7);
    LCD_WriteReg(0xD326, 0x02);
    LCD_WriteReg(0xD327, 0xCF);
    LCD_WriteReg(0xD328, 0x02);
    LCD_WriteReg(0xD329, 0xDE);
    LCD_WriteReg(0xD32A, 0x02);
    LCD_WriteReg(0xD32B, 0xF2);
    LCD_WriteReg(0xD32C, 0x02);
    LCD_WriteReg(0xD32D, 0xFE);
    LCD_WriteReg(0xD32E, 0x03);
    LCD_WriteReg(0xD32F, 0x10);
    LCD_WriteReg(0xD330, 0x03);
    LCD_WriteReg(0xD331, 0x33);
    LCD_WriteReg(0xD332, 0x03);
    LCD_WriteReg(0xD333, 0x6D);
    LCD_WriteReg(0xD400, 0x00);
    LCD_WriteReg(0xD401, 0x33);
    LCD_WriteReg(0xD402, 0x00);
    LCD_WriteReg(0xD403, 0x34);
    LCD_WriteReg(0xD404, 0x00);
    LCD_WriteReg(0xD405, 0x3A);
    LCD_WriteReg(0xD406, 0x00);
    LCD_WriteReg(0xD407, 0x4A);
    LCD_WriteReg(0xD408, 0x00);
    LCD_WriteReg(0xD409, 0x5C);
    LCD_WriteReg(0xD40A, 0x00);
    LCD_WriteReg(0xD40B, 0x81);

    LCD_WriteReg(0xD40C, 0x00);
    LCD_WriteReg(0xD40D, 0xA6);
    LCD_WriteReg(0xD40E, 0x00);
    LCD_WriteReg(0xD40F, 0xE5);
    LCD_WriteReg(0xD410, 0x01);
    LCD_WriteReg(0xD411, 0x13);
    LCD_WriteReg(0xD412, 0x01);
    LCD_WriteReg(0xD413, 0x54);
    LCD_WriteReg(0xD414, 0x01);
    LCD_WriteReg(0xD415, 0x82);
    LCD_WriteReg(0xD416, 0x01);
    LCD_WriteReg(0xD417, 0xCA);
    LCD_WriteReg(0xD418, 0x02);
    LCD_WriteReg(0xD419, 0x00);
    LCD_WriteReg(0xD41A, 0x02);
    LCD_WriteReg(0xD41B, 0x01);
    LCD_WriteReg(0xD41C, 0x02);
    LCD_WriteReg(0xD41D, 0x34);
    LCD_WriteReg(0xD41E, 0x02);
    LCD_WriteReg(0xD41F, 0x67);
    LCD_WriteReg(0xD420, 0x02);
    LCD_WriteReg(0xD421, 0x84);
    LCD_WriteReg(0xD422, 0x02);
    LCD_WriteReg(0xD423, 0xA4);
    LCD_WriteReg(0xD424, 0x02);
    LCD_WriteReg(0xD425, 0xB7);
    LCD_WriteReg(0xD426, 0x02);
    LCD_WriteReg(0xD427, 0xCF);
    LCD_WriteReg(0xD428, 0x02);
    LCD_WriteReg(0xD429, 0xDE);
    LCD_WriteReg(0xD42A, 0x02);
    LCD_WriteReg(0xD42B, 0xF2);
    LCD_WriteReg(0xD42C, 0x02);
    LCD_WriteReg(0xD42D, 0xFE);
    LCD_WriteReg(0xD42E, 0x03);
    LCD_WriteReg(0xD42F, 0x10);
    LCD_WriteReg(0xD430, 0x03);
    LCD_WriteReg(0xD431, 0x33);
    LCD_WriteReg(0xD432, 0x03);
    LCD_WriteReg(0xD433, 0x6D);
    LCD_WriteReg(0xD500, 0x00);
    LCD_WriteReg(0xD501, 0x33);
    LCD_WriteReg(0xD502, 0x00);
    LCD_WriteReg(0xD503, 0x34);
    LCD_WriteReg(0xD504, 0x00);
    LCD_WriteReg(0xD505, 0x3A);
    LCD_WriteReg(0xD506, 0x00);
    LCD_WriteReg(0xD507, 0x4A);
    LCD_WriteReg(0xD508, 0x00);
    LCD_WriteReg(0xD509, 0x5C);
    LCD_WriteReg(0xD50A, 0x00);
    LCD_WriteReg(0xD50B, 0x81);

    LCD_WriteReg(0xD50C, 0x00);
    LCD_WriteReg(0xD50D, 0xA6);
    LCD_WriteReg(0xD50E, 0x00);
    LCD_WriteReg(0xD50F, 0xE5);
    LCD_WriteReg(0xD510, 0x01);
    LCD_WriteReg(0xD511, 0x13);
    LCD_WriteReg(0xD512, 0x01);
    LCD_WriteReg(0xD513, 0x54);
    LCD_WriteReg(0xD514, 0x01);
    LCD_WriteReg(0xD515, 0x82);
    LCD_WriteReg(0xD516, 0x01);
    LCD_WriteReg(0xD517, 0xCA);
    LCD_WriteReg(0xD518, 0x02);
    LCD_WriteReg(0xD519, 0x00);
    LCD_WriteReg(0xD51A, 0x02);
    LCD_WriteReg(0xD51B, 0x01);
    LCD_WriteReg(0xD51C, 0x02);
    LCD_WriteReg(0xD51D, 0x34);
    LCD_WriteReg(0xD51E, 0x02);
    LCD_WriteReg(0xD51F, 0x67);
    LCD_WriteReg(0xD520, 0x02);
    LCD_WriteReg(0xD521, 0x84);
    LCD_WriteReg(0xD522, 0x02);
    LCD_WriteReg(0xD523, 0xA4);
    LCD_WriteReg(0xD524, 0x02);
    LCD_WriteReg(0xD525, 0xB7);
    LCD_WriteReg(0xD526, 0x02);
    LCD_WriteReg(0xD527, 0xCF);
    LCD_WriteReg(0xD528, 0x02);
    LCD_WriteReg(0xD529, 0xDE);
    LCD_WriteReg(0xD52A, 0x02);
    LCD_WriteReg(0xD52B, 0xF2);
    LCD_WriteReg(0xD52C, 0x02);
    LCD_WriteReg(0xD52D, 0xFE);
    LCD_WriteReg(0xD52E, 0x03);
    LCD_WriteReg(0xD52F, 0x10);
    LCD_WriteReg(0xD530, 0x03);
    LCD_WriteReg(0xD531, 0x33);
    LCD_WriteReg(0xD532, 0x03);
    LCD_WriteReg(0xD533, 0x6D);
    LCD_WriteReg(0xD600, 0x00);
    LCD_WriteReg(0xD601, 0x33);
    LCD_WriteReg(0xD602, 0x00);
    LCD_WriteReg(0xD603, 0x34);
    LCD_WriteReg(0xD604, 0x00);
    LCD_WriteReg(0xD605, 0x3A);
    LCD_WriteReg(0xD606, 0x00);
    LCD_WriteReg(0xD607, 0x4A);
    LCD_WriteReg(0xD608, 0x00);
    LCD_WriteReg(0xD609, 0x5C);
    LCD_WriteReg(0xD60A, 0x00);
    LCD_WriteReg(0xD60B, 0x81);

    LCD_WriteReg(0xD60C, 0x00);
    LCD_WriteReg(0xD60D, 0xA6);
    LCD_WriteReg(0xD60E, 0x00);
    LCD_WriteReg(0xD60F, 0xE5);
    LCD_WriteReg(0xD610, 0x01);
    LCD_WriteReg(0xD611, 0x13);
    LCD_WriteReg(0xD612, 0x01);
    LCD_WriteReg(0xD613, 0x54);
    LCD_WriteReg(0xD614, 0x01);
    LCD_WriteReg(0xD615, 0x82);
    LCD_WriteReg(0xD616, 0x01);
    LCD_WriteReg(0xD617, 0xCA);
    LCD_WriteReg(0xD618, 0x02);
    LCD_WriteReg(0xD619, 0x00);
    LCD_WriteReg(0xD61A, 0x02);
    LCD_WriteReg(0xD61B, 0x01);
    LCD_WriteReg(0xD61C, 0x02);
    LCD_WriteReg(0xD61D, 0x34);
    LCD_WriteReg(0xD61E, 0x02);
    LCD_WriteReg(0xD61F, 0x67);
    LCD_WriteReg(0xD620, 0x02);
    LCD_WriteReg(0xD621, 0x84);
    LCD_WriteReg(0xD622, 0x02);
    LCD_WriteReg(0xD623, 0xA4);
    LCD_WriteReg(0xD624, 0x02);
    LCD_WriteReg(0xD625, 0xB7);
    LCD_WriteReg(0xD626, 0x02);
    LCD_WriteReg(0xD627, 0xCF);
    LCD_WriteReg(0xD628, 0x02);
    LCD_WriteReg(0xD629, 0xDE);
    LCD_WriteReg(0xD62A, 0x02);
    LCD_WriteReg(0xD62B, 0xF2);
    LCD_WriteReg(0xD62C, 0x02);
    LCD_WriteReg(0xD62D, 0xFE);
    LCD_WriteReg(0xD62E, 0x03);
    LCD_WriteReg(0xD62F, 0x10);
    LCD_WriteReg(0xD630, 0x03);
    LCD_WriteReg(0xD631, 0x33);
    LCD_WriteReg(0xD632, 0x03);
    LCD_WriteReg(0xD633, 0x6D);
    // LV2 Page 0 enable
    LCD_WriteReg(0xF000, 0x55);
    LCD_WriteReg(0xF001, 0xAA);
    LCD_WriteReg(0xF002, 0x52);
    LCD_WriteReg(0xF003, 0x08);
    LCD_WriteReg(0xF004, 0x00);
    // Display control
    LCD_WriteReg(0xB100, 0xCC);
    LCD_WriteReg(0xB101, 0x00);
    // Source hold time
    LCD_WriteReg(0xB600, 0x05);
    // Gate EQ control
    LCD_WriteReg(0xB700, 0x70);
    LCD_WriteReg(0xB701, 0x70);
    // Source EQ control (Mode 2)
    LCD_WriteReg(0xB800, 0x01);
    LCD_WriteReg(0xB801, 0x03);
    LCD_WriteReg(0xB802, 0x03);
    LCD_WriteReg(0xB803, 0x03);
    // Inversion mode (2-dot)
    LCD_WriteReg(0xBC00, 0x02);
    LCD_WriteReg(0xBC01, 0x00);
    LCD_WriteReg(0xBC02, 0x00);
    // Timing control 4H w/ 4-delay
    LCD_WriteReg(0xC900, 0xD0);
    LCD_WriteReg(0xC901, 0x02);
    LCD_WriteReg(0xC902, 0x50);
    LCD_WriteReg(0xC903, 0x50);
    LCD_WriteReg(0xC904, 0x50);
    LCD_WriteReg(0x3500, 0x00);
    LCD_WriteReg(0x3A00, 0x55); // 16-bit/pixel
    LCD_WR_REG(0x1100);
    delay(120000);
    LCD_WR_REG(0x2900);

    id = (uint32_t)&MCU_LCD->LCD_RAM;
}
/**
 * @brief 初始化颜色条
 * 
 * @param buf_addr 颜色条缓冲区地址
 * @param width 颜色条宽度
 * @param height 颜色条高度
 */
void color_bar_init_rgb565(unsigned int buf_addr, unsigned int width, unsigned int height)
{
    unsigned int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < (width / 7); j++)
            writew((buf_addr + (i * width + j) * 2), RGB565_BLACK);
        for (j = (width / 7); j < (width * 2 / 7); j++)
            writew((buf_addr + (i * width + j) * 2), RGB565_YELLOW);
        for (j = (width * 2 / 7); j < (width * 3 / 7); j++)
            writew((buf_addr + (i * width + j) * 2), RGB565_WHITE);
        for (j = (width * 3 / 7); j < (width * 4 / 7); j++)
            writew((buf_addr + (i * width + j) * 2), RGB565_GREEN);
        for (j = (width * 4 / 7); j < (width * 5 / 7); j++)
            writew((buf_addr + (i * width + j) * 2), RGB565_MAGENTA);
        for (j = (width * 5 / 7); j < (width * 6 / 7); j++)
            writew((buf_addr + (i * width + j) * 2), RGB565_RED);
        for (j = (width * 6 / 7); j < width; j++)
            writew((buf_addr + (i * width + j) * 2), RGB565_BLUE);
    }
}

/**
 * @brief i8080 模块数据测试函数
 * 
 */
void i8080_data_test(void)
{
    int i, j;
    int width = 800;
    int height = 480;
    uint16_t *fb = (uint16_t *)0x1C000000;

    LCD_SetCursor(0x00, 0x0000); // 设置光标位置
    LCD_WriteRAM_Prepare();

    for (i = 0; i < 800; i++)
    {
        for (j = 0; j < 480; j++)
            MCU_LCD->LCD_RAM = RGB565_RED;
    }

    color_bar_init_rgb565(0x1c000000, 800, 480);

    LCD_Set_Window(0, 0, 800, 480); // 设置窗口
    LCD_SetCursor(0x00, 0x0000); // 设置光标位置
    LCD_WriteRAM_Prepare();

    for (i = 0; i < 480; i++) {
        for (j = 0; j < 800; j++) {
            LCD_WR_DATA(fb[i * 800 + j]);  // 传颜色值
        }
    }
}

/**
 * @brief i8080 模块DMA测试函数
 * 
 */
void i8080_data_dma_test(void)
{
    int i, j;
    int width = 800;
    int height = 480;
    axidma_handle_t axidma_handle;

    color_bar_init_rgb565(0x1c000000, 800, 480);

    LCD_Set_Window(0, 0, 800, 480); // 设置窗口
    LCD_SetCursor(0x00, 0x0000); // 设置光标位置
    LCD_WriteRAM_Prepare();

    axidma_handle.instance = AXI_DMAC1;
    axidma_handle.channel_num = AXI_DMAC_CH0;
    axidma_handle.src_msize = AXI_DMAC_MIZE_16;              // burst size 16
    axidma_handle.dst_msize = AXI_DMAC_MIZE_16;              // burst size 16
    axidma_handle.src_tr_width = AXI_DMAC_TRANSWIDTH_16_BITS; // transfer width 8 bits
    axidma_handle.dst_tr_width = AXI_DMAC_TRANSWIDTH_16_BITS; // transfer width 8 bits
    axidma_handle.src_inc = AXI_DMAC_SINC_INC;
    axidma_handle.dst_inc = AXI_DMAC_DINC_INC;
    axidma_handle.src_multblk_type = AXI_DMAC_MULTIBLK_SRC_CONTIGUOUS;
    axidma_handle.dst_multblk_type = AXI_DMAC_MULTIBLK_DST_CONTIGUOUS;
    axidma_handle.transfer_type = AXI_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA;

    axidma_handle.src_addr = (uint32_t)0x1c000000;
    axidma_handle.dst_addr = (uint32_t)&MCU_LCD->LCD_RAM;
    axidma_handle.nBlocks = 800*480 - 1;
    axidma_handle.irq_en = 0;
    axidma_handle.blk_tfr_en = 0;

    hal_axidma_init(&axidma_handle);
    hal_axidma_start(&axidma_handle);
    hal_axidma_transfer_polling(&axidma_handle);
    printf("DMA transfer done\r\n");
}


/**
 * @brief I8080 模块FMC初始化函数
 *
 */
void fmc_init(void)
{
    fmc_initstructure_t fmc_initstructure;
    fmc_initstructure.instance = I8080_CONTROLLER;
    fmc_initstructure.trc = 0x0f;
    fmc_initstructure.tas = 0x05;
    fmc_initstructure.twp = 0x00;
    fmc_initstructure.tbta = 0x01;
    fmc_initstructure.tprc = 0x00;
    hal_fmc_init(&fmc_initstructure);
}


/**
 * @brief I8080 模块测试示例函数
 *
 */
void i8080_demo(void)
{
    hal_cpm_sdram2lcd_module_set_div(CLK_DIV_10);
    
    printf("I8080 Demo\r\n");
    SwitchPinFunction(CLCD_CLLP_FUN, I8080_WR_FUN);
    SwitchPinFunction(CLCD_CLCP_FUN, I8080_RD_FUN);
    SwitchPinFunction(CLCD_CLFP_FUN, I8080_CS_FUN);
    SwitchPinFunction(CLCD_CLAC_FUN, I8080_RS_FUN);

    SwitchPinFunction(CLCD_DATA3_FUN, I8080_DATA0_FUN);
    SwitchPinFunction(CLCD_DATA4_FUN, I8080_DATA1_FUN);
    SwitchPinFunction(CLCD_DATA5_FUN, I8080_DATA2_FUN);
    SwitchPinFunction(CLCD_DATA6_FUN, I8080_DATA3_FUN);
    SwitchPinFunction(CLCD_DATA7_FUN, I8080_DATA4_FUN);

    SwitchPinFunction(CLCD_DATA10_FUN, I8080_DATA5_FUN);
    SwitchPinFunction(CLCD_DATA11_FUN, I8080_DATA6_FUN);
    SwitchPinFunction(CLCD_DATA12_FUN, I8080_DATA7_FUN);
    SwitchPinFunction(CLCD_DATA13_FUN, I8080_DATA8_FUN);
    SwitchPinFunction(CLCD_DATA14_FUN, I8080_DATA9_FUN);
    SwitchPinFunction(CLCD_DATA15_FUN, I8080_DATA10_FUN);

    SwitchPinFunction(CLCD_DATA19_FUN, I8080_DATA11_FUN);
    SwitchPinFunction(CLCD_DATA20_FUN, I8080_DATA12_FUN);
    SwitchPinFunction(CLCD_DATA21_FUN, I8080_DATA13_FUN);
    SwitchPinFunction(CLCD_DATA22_FUN, I8080_DATA14_FUN);
    SwitchPinFunction(CLCD_DATA23_FUN, I8080_DATA15_FUN);
    fmc_init();
    mcu_lcd_init();
    i8080_data_test();
    i8080_data_dma_test();
}

/** @} */ // 结束 I8080 模块分组
/** @} */ // 结束外设模块分组
