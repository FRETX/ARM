/*
This program is written by JAMAL

This program controls the LEDs connected with FretX V_6.1
Hardware connections are as follows
Row Anodes
    (Rows top to bottom)
    Row 1________P0
    Row 2________P1
    Row 3________P2
    Row 4________P3
    Row 5________P4
    Row 6________P5
Column Cathodes
    (Columns right to left)
    Col 1________P10
    Col 2________P9
    Col 3________P8
    Col 4________P7
    Col 5________P6
Status LED_______P29
*/

/*
include Libraries
*/

#include "mbed.h"
#include "BLEDevice.h"
#include "UARTService.h"
#include "nrf_temp.h"

/*
Define Device Parameters
*/

#define ADV_INTERVAL_MS         (1000UL)      // This is the advertising interval in milliseconds
#define DEVICE_NAME             ("FretX SAS") // This can be read AFTER connecting to the device.
#define SHORT_NAME              ("FretX")    // Keep this short: max 8 chars if a 128bit UUID is also advertised.
#define INTERVAL  (0.005F)                  // 0.005F is perfect interval
#define UART_BAUD_RATE          (115200UL)   // define the serial port baud rate


/*
Configure the peripherals
*/

bool OFF = 1;
bool ON = 0;
bool led1,led2,led3,led4,led5,led6,led11,led12,led13,led14,led15,led16,led21,led22,led23,led24,led25,led26,led31,led32,led33,led34,led35,led36,led41,led42,led43,led44,led45,led46;
int next = 0;
int byte1 = 0;
int byte2 = 0;
int byte3 = 0;
int byte4 = 0;
int byte5 = 0;
int byte6 = 0;
int byte7 = 0;
int byte8 = 0;

/*
Configure the peripherals
*/

BLEDevice   m_ble;
Serial      m_serial_port(p9, p11);  // TX pin, RX pin
DigitalOut  row1(p0);
DigitalOut  row2(p1);
DigitalOut  row3(p2);
DigitalOut  row4(p3);
DigitalOut  row5(p4);
DigitalOut  row6(p5);
DigitalOut  col1(p10);
DigitalOut  col2(p9);
DigitalOut  col3(p8);
DigitalOut  col4(p7);
DigitalOut  col5(p6);
DigitalOut  status_led(p29);
UARTService *m_uart_service_ptr;



/***************************** My Subroutines ***************************************/

void match(int integer)
{
    switch (integer)
    {
    case 1:
        led6 = 1;
        break;
    case 2:
        led5 = 1;
        break;
    case 3:
        led4 = 1;
        break;
    case 4:
        led3 = 1;
        break;
    case 5:
        led2 = 1;
        break;
    case 6:
        led1 = 1;
        break;
    
    case 11:
        led16 = 1;
        break;
    case 12:
        led15 = 1;
        break;
    case 13:
        led14 = 1;
        break;
    case 14:
        led13 = 1;;
        break;
    case 15:
        led12 = 1;
        break;
    case 16:
        led11 = 1;
        break;
        
    case 21:
        led26 = 1;
        break;
    case 22:
        led25 = 1;
        break;
    case 23:
        led24 = 1;
        break;
    case 24:
        led23 = 1;;
        break;
    case 25:
        led22 = 1;
        break;
    case 26:
        led21 = 1;
        break;
        
    case 31:
        led36 = 1;
        break;
    case 32:
        led35 = 1;
        break;
    case 33:
        led34 = 1;
        break;
    case 34:
        led33 = 1;;
        break;
    case 35:
        led32 = 1;
        break;
    case 36:
        led31 = 1;
        break;
        
    case 41:
        led46 = 1;
        break;
    case 42:
        led45 = 1;
        break;
    case 43:
        led44 = 1;
        break;
    case 44:
        led43 = 1;;
        break;
    case 45:
        led42 = 1;
        break;
    case 46:
        led41 = 1;
        break;
    }
}

void all_clear()
{
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    led5 = 0;
    led6 = 0;
    led11 = 0;
    led12 = 0;
    led13 = 0;
    led14 = 0;
    led15 = 0;
    led16 = 0;
    led21 = 0;
    led22 = 0;
    led23 = 0;
    led24 = 0;
    led25 = 0;
    led26 = 0;
    led31 = 0;
    led32 = 0;
    led33 = 0;
    led34 = 0;
    led35 = 0;
    led36 = 0;
    led41 = 0;
    led42 = 0;
    led43 = 0;
    led44 = 0;
    led45 = 0;
    led46 = 0;
}

void leds_off()
{
    row1 = ON;
    row2 = ON;
    row3 = ON;
    row4 = ON;
    row5 = ON;
    row6 = ON;
    col1 = OFF;
    col2 = OFF;
    col3 = OFF;
    col4 = OFF;
    col5 = OFF;
}

void off()
{
    col1 = OFF;
    col2 = OFF;
    col3 = OFF;
    col4 = OFF;
    col5 = OFF;
}

void row1_on()
{
    row1 = OFF;
    row2 = ON;
    row3 = ON;
    row4 = ON;
    row5 = ON;
    row6 = ON;
    //wait(0.003);
    //row1 = ON;
    //wait(0.020);
}

void row2_on()
{
    row2 = OFF;
    row1 = ON;
    row3 = ON;
    row4 = ON;
    row5 = ON;
    row6 = ON;
    //wait(0.003);
    //row2 = ON;
    //wait(0.020);
}

void row3_on()
{
    row3 = OFF;
    row2 = ON;
    row1 = ON;
    row4 = ON;
    row5 = ON;
    row6 = ON;
    //wait(0.003);
    //row3 = ON;
    //wait(0.020);
}

void row4_on()
{
    row4 = OFF;
    row2 = ON;
    row3 = ON;
    row1 = ON;
    row5 = ON;
    row6 = ON;
    //wait(0.003);
    //row4 = ON;
    //wait(0.020);
}

void row5_on()
{
    row5 = OFF;
    row2 = ON;
    row3 = ON;
    row4 = ON;
    row1 = ON;
    row6 = ON;
    //wait(0.003);
    //row5 = ON;
    //wait(0.020);
}

void row6_on()
{
    row6 = OFF;
    row2 = ON;
    row3 = ON;
    row4 = ON;
    row5 = ON;
    row1 = ON;
    //wait(0.003);
    //row6 = ON;
    //wait(0.020);
}

void set_col1()
{
    if(led1 == 1)
    {
        col1 = ON;
    }
    else
    {
        col1 = OFF;
    }
    
    if(led11 == 1)
    {
        col2 = ON;
    }
    else
    {
        col2 = OFF;
    }
    
    if(led21 == 1)
    {
        col3 = ON;
    }
    else
    {
        col3 = OFF;
    }
    
    if(led31 == 1)
    {
        col4 = ON;
    }
    else
    {
        col4 = OFF;
    }
    
    if(led41 == 1)
    {
        col5 = ON;
    }
    else
    {
        col5 = OFF;
    }
}

void set_col2()
{
    if(led2 == 1)
    {
        col1 = ON;
    }
    else
    {
        col1 = OFF;
    }
    
    if(led12 == 1)
    {
        col2 = ON;
    }
    else
    {
        col2 = OFF;
    }
    
    if(led22 == 1)
    {
        col3 = ON;
    }
    else
    {
        col3 = OFF;
    }
    
    if(led32 == 1)
    {
        col4 = ON;
    }
    else
    {
        col4 = OFF;
    }
    
    if(led42 == 1)
    {
        col5 = ON;
    }
    else
    {
        col5 = OFF;
    }
}

void set_col3()
{
    if(led3 == 1)
    {
        col1 = ON;
    }
    else
    {
        col1 = OFF;
    }
    
    if(led13 == 1)
    {
        col2 = ON;
    }
    else
    {
        col2 = OFF;
    }
    
    if(led23 == 1)
    {
        col3 = ON;
    }
    else
    {
        col3 = OFF;
    }
    
    if(led33 == 1)
    {
        col4 = ON;
    }
    else
    {
        col4 = OFF;
    }
    
    if(led43 == 1)
    {
        col5 = ON;
    }
    else
    {
        col5 = OFF;
    }
}

void set_col4()
{
    if(led4 == 1)
    {
        col1 = ON;
    }
    else
    {
        col1 = OFF;
    }
    
    if(led14 == 1)
    {
        col2 = ON;
    }
    else
    {
        col2 = OFF;
    }
    
    if(led24 == 1)
    {
        col3 = ON;
    }
    else
    {
        col3 = OFF;
    }
    
    if(led34 == 1)
    {
        col4 = ON;
    }
    else
    {
        col4 = OFF;
    }
    
    if(led44 == 1)
    {
        col5 = ON;
    }
    else
    {
        col5 = OFF;
    }
}

void set_col5()
{
    if(led5 == 1)
    {
        col1 = ON;
    }
    else
    {
        col1 = OFF;
    }
    
    if(led15 == 1)
    {
        col2 = ON;
    }
    else
    {
        col2 = OFF;
    }
    
    if(led25 == 1)
    {
        col3 = ON;
    }
    else
    {
        col3 = OFF;
    }
    
    if(led35 == 1)
    {
        col4 = ON;
    }
    else
    {
        col4 = OFF;
    }
    
    if(led45 == 1)
    {
        col5 = ON;
    }
    else
    {
        col5 = OFF;
    }
}

void set_col6()
{
    if(led6 == 1)
    {
        col1 = ON;
    }
    else
    {
        col1 = OFF;
    }
    
    if(led16 == 1)
    {
        col2 = ON;
    }
    else
    {
        col2 = OFF;
    }
    
    if(led26 == 1)
    {
        col3 = ON;
    }
    else
    {
        col3 = OFF;
    }
    
    if(led36 == 1)
    {
        col4 = ON;
    }
    else
    {
        col4 = OFF;
    }
    
    if(led46 == 1)
    {
        col5 = ON;
    }
    else
    {
        col5 = OFF;
    }
}




/************************************************************************************/

/**
 * This callback is used whenever BLE will be connected.
 */

void connectionCallback(Gap::Handle_t handle, Gap::addr_type_t peerAddrType, const Gap::address_t peerAddr, const Gap::ConnectionParams_t * connectionParams)
{
    status_led = ON;
}


/**
 * This callback is used whenever a disconnection occurs.
 */
void disconnectionCallback(Gap::Handle_t handle, Gap::DisconnectionReason_t reason)
{
    all_clear();
    switch (reason) {
    case Gap::REMOTE_USER_TERMINATED_CONNECTION:
        status_led = OFF;
        break;
    case Gap::LOCAL_HOST_TERMINATED_CONNECTION:
        status_led = OFF;
        break;
    case Gap::CONN_INTERVAL_UNACCEPTABLE:
        //status_led = OFF;
        break;
    }

    /* Start Advertising */
    m_ble.startAdvertising();
}




/**
 * This callback is used whenever the host writes data to one of our GATT characteristics.
 */
void dataWrittenCallback(const GattCharacteristicWriteCBParams *params)
{
    // Ensure that initialization is finished and the host has written to the TX characteristic.
    if ((m_uart_service_ptr != NULL) && (params->charHandle == m_uart_service_ptr->getTXCharacteristicHandle())) {
        uint8_t  buf[20];
        uint32_t len = 0;
        all_clear();
        /** get byte 1 **/

        if (params->len > 0) {
            switch (params->data[0]) {
            case 0:
                off();
                break;
            default:
                match(params->data[0]);
                break;
            }
        }
        
        /** get byte 2 **/
        
        if (params->len > 1) {
            switch (params->data[1]) {
            case 0:
                break;
            default:
                match(params->data[1]);
                break;
            }
        }
        
        /** get byte 3 **/
        
        if (params->len > 2) {
            switch (params->data[2]) {
            case 0:
                break;
            default:
                match(params->data[2]);
                break;
            }
        }
        
        /** get byte 4 **/
        
        if (params->len > 3) {
            switch (params->data[3]) {
            case 0:
                break;
            default:
                match(params->data[3]);
                break;
            }
        }
        
        /** get byte 5 **/
        
        if (params->len > 4) {
            switch (params->data[4]) {
            case 0:
                break;
            default:
                match(params->data[4]);
                break;
            }
        }
        
        /** get byte 6 **/
        
        if (params->len > 5) {
            switch (params->data[5]) {
            case 0:
                break;
            default:
                match(params->data[5]);
                break;
            }
        }
        
        /** get byte 7 **/
        
        if (params->len > 6) {
            switch (params->data[6]) {
            case 0:
                break;
            default:
                match(params->data[6]);
                break;
            }
        }
        
        /** get byte 8 **/
        
        if (params->len > 7) {
            switch (params->data[7]) {
            case 0:
                break;
            default:
                match(params->data[7]);
                break;
            }
        }
        
        /** get byte 9 **/
        
        if (params->len > 8) {
            switch (params->data[8]) {
            case 0:
                break;
            default:
                match(params->data[8]);
                break;
            }
        }

        m_ble.updateCharacteristicValue(m_uart_service_ptr->getRXCharacteristicHandle(), buf, len);
    }
}


/**
 * This callback is used whenever a write to a GATT characteristic causes data to be sent to the host.
 */
void dataSentCallback(unsigned count)
{
    
}

/**
 * This callback is scheduled to be called periodically via a low-priority interrupt.
 */
void periodicCallback(void)
{
    switch(next)
    {
        case 0:
        off();
        set_col1();
        row1_on();
        next = 1;
        //off();
        break;
        
        case 1:
        off();
        set_col2();
        row2_on();
        next = 2;
        //off();
        break;
        
        case 2:
        off();
        set_col3();
        row3_on();
        next = 3;
        //off();
        break;
        
        case 3:
        off();
        set_col4();
        row4_on();
        next = 4;
        //off();
        break;
        
        case 4:
        off();
        set_col5();
        row5_on();
        next = 5;
        //off();
        break;
        
        case 5:
        off();
        set_col6();
        row6_on();
        next = 0;
        //off();
        break;
    }
}


void error(ble_error_t err, uint32_t line)
{
    
}

int main(void)
{
    ble_error_t err;
    Ticker      ticker;
    
    ticker.attach(periodicCallback, INTERVAL);
    
    leds_off();         //switch off all the LEDs

    m_ble.init();
    
    m_ble.onDisconnection(disconnectionCallback);
    m_ble.onConnection(connectionCallback);
    m_ble.onDataWritten(dataWrittenCallback);
    m_ble.onDataSent(dataSentCallback);

    /*
    Set the TX power in dBm units.
    Possible values (in decreasing order): 4, 0, -4, -8, -12, -16, -20.
    */
    err = m_ble.setTxPower(4);
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    /* Setup advertising (GAP stuff) */
    err = m_ble.setDeviceName(DEVICE_NAME);
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    err = m_ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED);
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    m_ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);

    err = m_ble.accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,
                                                (const uint8_t *)SHORT_NAME,
                                                (sizeof(SHORT_NAME) - 1));
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    err = m_ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_128BIT_SERVICE_IDS,
                                                (const uint8_t *)UARTServiceUUID_reversed,
                                                sizeof(UARTServiceUUID_reversed));
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    m_ble.setAdvertisingInterval(Gap::MSEC_TO_ADVERTISEMENT_DURATION_UNITS(ADV_INTERVAL_MS));
    m_ble.startAdvertising();

    /* Create a UARTService object (GATT stuff) */
    UARTService uartService(m_ble);
    m_uart_service_ptr = &uartService;

    while (true) 
    {
        m_ble.waitForEvent();
    }
}
