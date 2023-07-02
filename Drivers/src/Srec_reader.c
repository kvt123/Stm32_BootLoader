#include <stdint.h>
#include "Srec_reader.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
static parse_status_t status;
static uint32_t numberOfSrecDataLine=0;
static address_bit_type_t addressBitType = address_defaule;

/*******************************************************************************
 * static fuction
 ******************************************************************************/
static uint8_t convert_to_hex(uint8_t hex);
static uint8_t convert_twoHex2byte(uint8_t *input);
static uint16_t convert_16bit2dec(uint8_t *input);
static uint32_t convert_24bit2dec(uint8_t *input);

/*******************************************************************************
 * code
 ******************************************************************************/

/* function convert from hex number to dec number */
static uint8_t convert_to_hex(uint8_t hex)
{
    uint8_t value;
    /*characters is 0-9*/
    if((hex >= '0') && (hex <= '9'))
    {
        value = hex - '0';
    }
    /*characters is A-F*/
    else if((hex >= 'A') && (hex <= 'F'))
    {
        value = hex - 'A' + 10;
    }
    /*others character*/
    else
    {
        value = 0xff;
    }

    return value;
}

/* function convert 2 hex to form 1 byte */
static uint8_t convert_twoHex2byte(uint8_t *input)
{
    uint8_t value=0u;
    value = (convert_to_hex(input[0])<<4 | convert_to_hex(input[1]));
    return value;
}

/* function convert 2 character(16 bit) hex to form dec */
static uint16_t convert_16bit2dec(uint8_t *input)
{
    uint16_t value=0u;
    value = ((convert_to_hex(input[0])<<12) |
            (convert_to_hex(input[1])<<8) |
            (convert_to_hex(input[2])<<4) |
            (convert_to_hex(input[3])));

    return value;
}

/* function convert 3 character(24 bit) hex to form dec */
static uint32_t convert_24bit2dec(uint8_t *input)
{
    uint32_t value =0u;
    value = ((convert_to_hex(input[0])<<20) |
            (convert_to_hex(input[1])<<16) |
            (convert_to_hex(input[2])<<12) | 
            (convert_to_hex(input[3]))<<8 |
            (convert_to_hex(input[4]))<<4 |
            (convert_to_hex(input[5])));

    return value;
}


/* fuction parse each srec line */
parse_status_t parseData(uint8_t pInput[],parse_data_line_struct_t *Output)
{
    uint8_t checkvalue = 0;
    uint8_t CheckSum =0;
    uint32_t ByteCount = convert_twoHex2byte(&pInput[2]);
    uint8_t srecType = convert_to_hex(pInput[1]);
    uint32_t addressLength =0;
    uint32_t dataIndex=0;
    Output->address = 0;
    /* check invalid srec record */
    if(pInput[0]!= 'S')
    {
        return e_parseStatus_error;
    }

    switch (srecType)
    {
        case 0:
            status = e_parseStatus_inprogress;
            addressBitType = address_defaule;
            Output->dataLength = ByteCount - 3;
            addressLength =2;
            break;
        case 1:
            if(addressBitType == address_defaule)
            {
                addressBitType = address_16bit;
                numberOfSrecDataLine++;
                status = e_parseStatus_inprogress;
                addressLength =2;
                Output->dataLength = ByteCount - 1 - addressLength;
            }
            else if(addressBitType != address_16bit)
            {
                status = e_parseStatus_error;
            }
            else
            {
                addressBitType = address_16bit;
                numberOfSrecDataLine++;
                status = e_parseStatus_inprogress;
                addressLength =2;
                Output->dataLength = ByteCount - 1 - addressLength;
            }
            break;
        case 2:
            if(addressBitType == address_defaule)
            {
                addressBitType = address_24bit;
                numberOfSrecDataLine++;
                status = e_parseStatus_inprogress;
                addressLength =3;
                Output->dataLength = ByteCount - 1 - addressLength;
            }
            else if(addressBitType != address_24bit)
            {
                status = e_parseStatus_error;
            }
            else
            {
                addressBitType = address_24bit;
                numberOfSrecDataLine++;
                status = e_parseStatus_inprogress;
                addressLength =3;
                Output->dataLength = ByteCount - 1 - addressLength;
            }
            break;
        case 3:
            if(addressBitType == address_defaule)
            {
                addressBitType = address_32bit;
                numberOfSrecDataLine++;
                status = e_parseStatus_inprogress;
                addressLength =4;
                Output->dataLength = ByteCount - 1 - addressLength;
            }
            else if(addressBitType != address_32bit)
            {
                status = e_parseStatus_error;
            }
            else
            {
                addressBitType = address_32bit;
                numberOfSrecDataLine++;
                status = e_parseStatus_inprogress;
                addressLength =4;
                Output->dataLength = ByteCount - 1 - addressLength;
            }
            break;
        case 4:
            Output->dataLength = 0;
            break;
        case 5:
            /* check number of srec data line */
            if((convert_16bit2dec(&pInput[(4)]) != numberOfSrecDataLine) || (numberOfSrecDataLine > 0xFFFF))
            {
                status = e_parseStatus_error;
                numberOfSrecDataLine =0;
            }
            else
            {
                status = e_parseStatus_done;
                numberOfSrecDataLine =0;
            }
            Output->dataLength = 0;
            addressLength =2;
            break;
        case 6:
            /* check number of srec data line */
            if((convert_24bit2dec(&pInput[(4+ addressLength*2)]) != numberOfSrecDataLine) || (numberOfSrecDataLine < 0xFFFF) || (numberOfSrecDataLine > 0xFFFFFF))
            {
                status = e_parseStatus_error;
                numberOfSrecDataLine =0;
            }
            else
            {
                status = e_parseStatus_done;
                numberOfSrecDataLine =0;
            }
            addressLength =3;
            Output->dataLength = 0;
            break;
        case 7:
            /* check end of S3 record */
            if(addressBitType == address_32bit)
            {
                status = e_parseStatus_done;
            }
            else 
            {
                status = e_parseStatus_error;
            }
            addressLength =4;
            Output->dataLength = 0;
            break;
        case 8:
            /* check end of S2 record */
            if(addressBitType == address_24bit)
            {
                status = e_parseStatus_done;
            }
            else 
            {
                status = e_parseStatus_error;
            }
            addressLength =3;
            Output->dataLength = 0;
            break;
        case 9:
            /* check end of S1 record */
            if(addressBitType == address_16bit)
            {
                status = e_parseStatus_done;
            }
            else 
            {
                status = e_parseStatus_error;
            }
            addressLength =2;
            Output->dataLength = 0;
            break;
        default:
            status = e_parseStatus_error;
            break;
    }
    /* covert address */
     for (dataIndex = 4; dataIndex < addressLength*2+4; dataIndex += 2)
        {
            Output->address |= (convert_twoHex2byte(&pInput[dataIndex]))<<(8*(addressLength+1-dataIndex/2)); /*address of line srec*/
        }
    /* add data to buffer data */
        while (dataIndex < (Output->dataLength*2+4+addressLength*2))
        {
            Output->data[(dataIndex-(addressLength*2+4))/2] = (convert_twoHex2byte(&pInput[dataIndex]));     /*Data of line srec*/
            dataIndex += 2;
        }
    /* check sum */
    CheckSum = convert_twoHex2byte(&pInput[4+addressLength*2+2* Output->dataLength]);

    /* check value */
    for(dataIndex=2;dataIndex<(4+addressLength*2+2* Output->dataLength);dataIndex+=2)
    {
        checkvalue = checkvalue + convert_twoHex2byte(&pInput[dataIndex]);
    }
    checkvalue = ((uint8_t)~checkvalue) & 0xFF;
    if (checkvalue != CheckSum)
    {
        status = e_parseStatus_error;
    }

    return status;
}
