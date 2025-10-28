
#include "type.h"
#include "usb_drv.h"
#include "usb_protocol.h"
#include "usb_cdc_protocol.h"

const uint8_t usb_cdc_Device_Descriptor[18] = // USB设备描述符
    {
        0x12,       // bLength: 0x12 字节
        DT_DEVICE,  // bDescriptorType: 设备
        0x00, 0x02, // bcdusb_cdc: version2.0
        0x02,       // bDeviceClass字段。本设备必须在设备描述符中指定设备的类型，
              // 否则，由于在配置集合中有两个接口，就会被系统认为是一个USB复合设备，从而导致设备工作不正常。0x02为通信设备类的类代码。
        0x00,                    // bDeviceSubClass: 子类0，必须为0
        0x00,                    // bDeviceProtocol: 协议0，必须为0
        USB_MAX_PACKET_SIZE_EP0, // bMaxPacketSize0: 64字节（端点0的最大包长）
        0xD0, 0x2F,              // idVendor:  国芯科技厂商 ID
        0x07, 0x00,              // idProduct: 产品 ID
        0x00, 0x01,              // bcdDevice: 设备版本
        0x01,                    // iManufacturer: 字符串索引
        0x02,                    // iProduct: 字符串索引
        0x03,                    // iSerialNumber: 字符串索引
        0x01,                    // bNumConfigurations:支持的配置数1
};

// Device Qualifier Descriptor
const uint8_t usb_cdc_Device_Qualifier_Descriptor[10] =
    {
        0x0A,                    // bLength: 0x12 bytes
        DT_DEVICE_QUALIFIER,     // bDescriptorType: DEVICE
        0x00, 0x02,              // bcdUSB: version 2.0
        0x00,                    // bDeviceClass: independent interfaces
        0x00,                    // bDeviceSubClass: 0
        0x00,                    // bDeviceProtocol: class specific protocols NOT used on device basis
        USB_MAX_PACKET_SIZE_EP0, // bMaxPacketSize0 for other speed
        0x01,                    // bNumConfigurations for other-speed configuration
        0x00,                    // Reserved,must be 0
};

// USB配置描述符
const uint8_t usb_cdc_Configuration_Descriptor[] =
    {
        0x09,                           // bLength
        DT_CONFIGURATION,               // bDescriptor
        _byte_low(USB_CDC_CONFIG_LEN),  // wTotalLength  该集合的总长度  低字节
        _byte_high(USB_CDC_CONFIG_LEN), // wTotalLength  该集合的总长度  高字节
        0x02,                           // bNumInterface
        0x01,                           // bConfiguration Value
        0x00,                           // iConfiguration
        0xA0,                           // bmAttributes,BUS-POWER
        0x32,                           // bMaxPower,200mA

        /*******************CDC类接口描述符*********************/
        0x09,           // bLength:    接口描述符长度
        INTERFACE_TYPE, // bDescriptorType   接口描述符
        0x00,           // bInterfaceNumber   接口编号
        0x00,           // bAlternateSetting   接口备用编号
        0x01,           // bNumEndpoints     非0端点数,CDC接口只使用一个中断
        0x02,           // bInterfaceClass:   该接口所使用的类。CDC类的类代码为0x02。
        0x02,           // bInterfaceSubClass  该接口所使用的子类。要实现USB转串口，
              // 就必须使用Abstract Control Model（抽象控制模型）子类。它的编号为0x02。
        0x01, // bInterfaceProtocol 使用Common AT Commands（通用AT命令）协议。该协议的编号为0x01。
        0x00, // iInterface   该接口的字符串索引值。这里没有，为0。
        /***************以下为功能描述符****************/
        /********* Header Functional Descriptor ********/
        0x05,       // bFunctionLength字段。该描述符长度为5字节
        0x24,       // bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
        0x00,       // bDescriptorSubtype字段。描述符子类为Header Functional Descriptor编号为0x00。
        0x10, 0x01, // bcdCDC字段。CDC版本号，为0x0110（低字节在先）
        /**** Call Management Functional Descriptor ****/
        0x05, // bFunctionLength字段。该描述符长度为5字节
        0x24, // bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
        0x01, // bDescriptorSubtype字段。描述符子类为Call Management functional descriptor，编号为0x01。
        0x00, // bmCapabilities字段。设备自己不管理call management
        0x00, // bDataInterface字段。没有数据类接口用作call management
        /*** Abstract Control Management Functional Descriptor ***/
        0x04, // bFunctionLength字段。该描述符长度为4字节
        0x24, // bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
        0x02, // bDescriptorSubtype字段。描述符子类为Abstract Control Management functional descriptor，编号为0x02。
        0x02, // bmCapabilities字段。支持Set_Line_Coding、Set_Control_Line_State、Get_Line_Coding请求和Serial_State通知
        /***  Union Functional Descriptor  **/
        0x05, // bFunctionLength字段。该描述符长度为5字节。
        0x24, // bDescriptorType字段。描述符类型为类特殊接口（CS_INTERFACE）编号为0x24。
        0x06, // bDescriptorSubtype字段。描述符子类为Union functional descriptor，编号为0x06。
        0x00, // MasterInterface字段。这里为前面编号为0的CDC接口。
        0x01, // SlaveInterface字段，这里为接下来编号为1的数据类接口。
        /***********  以下为接口0的端点描述符  *******/
        0x07,                                // bLength字段。端点描述符长度为7字节。
        DT_ENDPOINT,                         // bDescriptorType字段。端点描述符编号为0x05。
        0x80 + BULKIN_INT,                   // bEndpointAddress字段。端点的地址。这里使用输入端点3。D7位表示数据方向，输入端点D7为1。所以输入端点3的地址为0x83。
        TRANS_INT,                           // bmAttributes字段。D1~D0为端点传输类型选择。该端点为中断端点。中断端点的编号为3。其它位保留为0。
        _byte_low(USB_MAX_PACKET_SIZE_V20),  // wMaxPacketSize字段。该端点的最大包长 低字节
        _byte_high(USB_MAX_PACKET_SIZE_V20), // wMaxPacketSize字段。该端点的最大包长 高字节
        0x01,                                // bInterval字段。端点查询的时间，这里设置为10个帧时间，即10ms。
        /*********  以下为接口1（数据接口）的接口描述符  *********/
        0x09,           // bLength字段。接口描述符的长度为9字节。
        INTERFACE_TYPE, // bDescriptorType字段。接口描述符的编号为0x04。
        0x01,           // bInterfaceNumber字段。该接口的编号，第二个接口，编号为1。
        0x00,           // bAlternateSetting字段。该接口的备用编号，为0。
        0x02,           // bNumEndpoints字段。非0端点的数目。该设备需要使用一对批量端点，设置为2。
        0x0A,           // bInterfaceClass字段。该接口所使用的类。数据类接口的代码为0x0A。
        0x00,           // bInterfaceSubClass字段。该接口所使用的子类为0。
        0x00,           // bInterfaceProtocol字段。该接口所使用的协议为0。
        0x00,           // iConfiguration字段。该接口的字符串索引值。这里没有，为0。
        /*****  以下为接口1（数据类接口）的端点描述符  *****/
        /*************** 批量输入端点1描述符 ******************/
        0x07,                                // bLength字段。端点描述符长度为7字节。
        DT_ENDPOINT,                         // bDescriptorType字段。端点描述符编号为0x05。
        0x80 + BULKIN_EP,                    // bEndpointAddress字段。端点的地址。我们使用输入端点1。D7位表示数据方向，输入端点D7为1。所以输入端点1的地址为0x81。
        TRANS_BULK,                          // bmAttributes字段。D1~D0为端点传输类型选择。该端点为批量端点，批量端点的编号为0x02。其它位保留为0。
        _byte_low(USB_MAX_PACKET_SIZE_V20),  // wMaxPacketSize字段。该端点的最大包长 低字节
        _byte_high(USB_MAX_PACKET_SIZE_V20), // wMaxPacketSize字段。该端点的最大包长 高字节
        0x00,                                // bInterval字段。端点查询的时间，这里对批量端点无效。
        /*************** 批量输出端点2描述符 ******************/
        0x07,                                // bLength字段。端点描述符长度为7字节。
        DT_ENDPOINT,                         // bDescriptorType字段。端点描述符编号为0x05。
        BULKOUT_EP,                          // bEndpointAddress字段。端点的地址。我们使用输入端点2。D7位表示数据方向，输入端点D7为1。所以输入端点2的地址为0x82。
        TRANS_BULK,                          // bmAttributes字段。D1~D0为端点传输类型选择。该端点为批量端点，批量端点的编号为0x02。其它位保留为0。
        _byte_low(USB_MAX_PACKET_SIZE_V20),  // wMaxPacketSize字段。该端点的最大包长 低字节
        _byte_high(USB_MAX_PACKET_SIZE_V20), // wMaxPacketSize字段。该端点的最大包长 高字节
        0x00,                                // bInterval字段。端点查询的时间，这里对批量端点无效。
};

// USB Language ID
const uint8_t usb_cdc_LanguageID[4] =
    {
        4,         // Num bytes of this descriptor
        DT_STRING, // String descriptor
        0x09,      // Language ID LSB
        0x04       // Language ID
};

// Manufacturer String
const uint8_t usb_cdc_StrDescManufacturer[12] =
    {
        12,        // Num bytes of this descriptor
        DT_STRING, // String descriptor
        'C', 0,
        'C', 0,
        'o', 0,
        'r', 0,
        'e', 0};

// Product String
const uint8_t usb_cdc_StrDescProduct[30] =
    {
        30,        // Num bytes of this descriptor
        DT_STRING, // String descriptor
        'U', 0,
        'S', 0,
        'B', 0,
        ' ', 0,
        'C', 0,
        'D', 0,
        'C', 0,
        ' ', 0,
        'D', 0,
        'E', 0,
        'V', 0,
        'I', 0,
        'C', 0,
        'E', 0};

// Serial Number
const uint8_t usb_cdc_StrDescSerialNumber[34] =
    {
        34,        // Num bytes of this descriptor
        DT_STRING, // String descriptor
        '1', 0,
        '2', 0,
        '3', 0,
        '4', 0,
        '5', 0,
        '6', 0,
        '7', 0,
        '8', 0,
        '9', 0,
        '0', 0,
        'A', 0,
        'B', 0,
        'C', 0,
        'D', 0,
        'E', 0,
        'F', 0};

uint8_t usb_cdc_LineCoding[7] =
    {
        0x80, 0x25,       // 9600,
        0x00, 0x00, 0x00, // 无校验
        0x00, 0x08        // 8bit
};
