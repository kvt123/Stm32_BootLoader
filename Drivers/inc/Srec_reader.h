#ifndef _SREC_READER_H_
#define _SREC_READER_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_DATA_SIZE                    80
/*******************************************************************************
 * Typedef
 ******************************************************************************/

/* Return code by parsing function */
typedef enum {
    e_parseStatus_done = 0U,
    e_parseStatus_inprogress = 1U,
    e_parseStatus_error = 2U,
    e_parseStatus_undefined = 3U
} parse_status_t;

/* type of address in one srec line */
typedef enum
{
    address_header = 0u,
    address_16bit =1u,
    address_24bit = 2u,
    address_32bit=3u,
    address_defaule = 4u
}address_bit_type_t;

/* type of parameter public for output of parseData fuction */
typedef struct
{
    uint32_t address;
    uint8_t data[MAX_DATA_SIZE];
    uint8_t dataLength;
} parse_data_line_struct_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 *@brief fuction parse each srec line
 *@param
 */
parse_status_t parseData(uint8_t pInput[],parse_data_line_struct_t *Output);

#endif /* _SREC_READER_H_ */
