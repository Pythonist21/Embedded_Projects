#include "stdio.h"
#include "cyhal.h"
#include "cybsp.h"
#include "GUI.h"
#include "mtb_e2271cs021.h"
#include "LCDConf.h"
#include "cy8ckit_028_epd_pins.h"
#include "cy_retarget_io.h"
#include "mtb_bmi160.h"
#define  IDLE_VECTOR 16472 //The average value of resulting vector for motion sensor in idling mode
//--------------------------
#include "inttypes.h"
#include "math.h"
//--------------------------
#define IMU_I2C_SDA (CYBSP_I2C_SDA)
#define IMU_I2C_SCL (CYBSP_I2C_SCL)
// #define THRESHOLD 500 // Value of experimental tnreshold, curently unused
//------------------------------------------------------
float calibrate(void);
char *convert_to_string(uint16_t val); //Currently unused
void calc_of_steps(int16_t *total_v, int16_t *previous_v, uint16_t *step_count, const int *tres_hold);
void eink_init(cy_rslt_t result);
void bmi_init(cy_rslt_t result);
//------------------------------------------------------
cyhal_spi_t spi;
//EINK_DISPLAY_PINOUT_INIT---------------------------------------------
const mtb_e2271cs021_pins_t pins =
{
    .spi_mosi = CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MOSI,
    .spi_miso = CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MISO,
    .spi_sclk = CY8CKIT_028_EPD_PIN_DISPLAY_SPI_SCLK,
    .spi_cs = CY8CKIT_028_EPD_PIN_DISPLAY_CS,
    .reset = CY8CKIT_028_EPD_PIN_DISPLAY_RST,
    .busy = CY8CKIT_028_EPD_PIN_DISPLAY_BUSY,
    .discharge = CY8CKIT_028_EPD_PIN_DISPLAY_DISCHARGE,
    .enable = CY8CKIT_028_EPD_PIN_DISPLAY_EN,
    .border = CY8CKIT_028_EPD_PIN_DISPLAY_BORDER,
    .io_enable = CY8CKIT_028_EPD_PIN_DISPLAY_IOEN,
};

uint8_t previous_frame[PV_EINK_IMAGE_SIZE] = {0};
uint8_t *current_frame;
//ERROR_HANDLER--------------------------------------------------------
void handle_error(void)
{
     /* Disable all interrupts. */
    __disable_irq();

    CY_ASSERT(0);
}
//MOTION_SENSOR_INIT---------------------------------------------------
mtb_bmi160_t motion_sensor;
cyhal_i2c_t i2c;
cyhal_i2c_cfg_t i2c_cfg = {
    .is_slave = false,
    .address = 0,
    .frequencyhal_hz = 400000
};

int main(void)
{
    /* Declaration of global variables for calculation of steps */
    int16_t vectorprevious = 0;
    int16_t totalvector = 0;
    uint16_t stepcounter = 0;
    float step_calibration = 0;
    //------------------------------------------------------------------------
    cy_rslt_t result;
    /* Initialize the device and board peripherals */
    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
    	handle_error();
    }
    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    if (result != CY_RSLT_SUCCESS)
    {
    	handle_error();
    }
    /* Initialize motion sensor*/
    bmi_init(result);
    __enable_irq(); //Enable global interrupts
    /* Initialize SPI and EINK display */
    eink_init(result);
    GUI_Clear();
    GUI_DispStringAt("Step Counter Demo", (LCD_GetXSize() / 2), (LCD_GetYSize() / 2) - (GUI_GetFontSizeY() / 2));
    mtb_e2271cs021_show_frame(previous_frame, current_frame, MTB_E2271CS021_FULL_4STAGE, true);
    cyhal_system_delay_ms(100);
    printf("Step Counter Demo\n");
    step_calibration = calibrate();
    printf("Vector:%f\n", step_calibration);
    const int treshold = fabs((int)(step_calibration - IDLE_VECTOR)); //calculating of treshold
    printf("Treshold:%d\n", treshold);
    for (;;)
    {	    	/*____________*/
    	if((step_calibration - IDLE_VECTOR) <= 50) // Falling of calibration condition
    	{
    		GUI_Clear();
    		GUI_DispStringAt("Fault of calibration", 0 , 0);
    		mtb_e2271cs021_show_frame(previous_frame, current_frame, MTB_E2271CS021_FULL_4STAGE, true);
    	}
    	else
    	{
    		if(0UL == Cy_GPIO_Read(P0_4_PORT, P0_4_NUM))//Polling the state of SW2, if true reset counter
    		{
    		    stepcounter=0;
    		    GUI_Clear();
    		    GUI_DispStringAt("Reset Counter", 0 , 0);
    		    mtb_e2271cs021_show_frame(previous_frame, current_frame, MTB_E2271CS021_FULL_4STAGE, true);
    		}
    		else
    		{
    		    mtb_bmi160_data_t data;
    		    GUI_Clear();
    		    GUI_DispStringAt("Step", 0 , 0);
    		    mtb_bmi160_read(&motion_sensor, &data);
    		    calc_of_steps(&totalvector, &vectorprevious, &stepcounter, &treshold);
    		    printf("Step:%d\n", stepcounter);
    		    GUI_DispStringAtCEOL(convert_to_string(stepcounter), 60, 0);
    		    mtb_e2271cs021_show_frame(previous_frame, current_frame, MTB_E2271CS021_FULL_4STAGE, true);
    		}
    	}
    }
}

/* Function that calibrates the sensor for an individual human step */
float calibrate(void)
{
	uint16_t vector_data[100]={0}; //Array for the storing of values of
	float vector=0;
	GUI_DispStringAt("Make some steps", 0 , 0);
	GUI_DispStringAt("For calibration", 0 , 30);
	mtb_e2271cs021_show_frame(previous_frame, current_frame, MTB_E2271CS021_FULL_4STAGE, true);
	mtb_bmi160_data_t data;
	mtb_bmi160_read(&motion_sensor, &data);
	for(int i=0; i<100; i++)
	{
	    vector_data[i] = sqrt( (data.accel.x*data.accel.x) + (data.accel.y*data.accel.y) + (data.accel.z*data.accel.z) );
	    cyhal_system_delay_ms(50);
	}
	for(int i=0; i<100; i++)
	{
	    vector += vector_data[i];
	}
	    vector=vector/100;
	    return vector;
	 }

/*Function for converting integer value in string */
char *convert_to_string(uint16_t val)
{
     char *str = calloc(6, sizeof(int));
     sprintf(str, "%d", val);
     return str;
}

/* Function for calculating of steps.
 * It read's the values of acceleration on X, Y, Z axis.
 * Calculates the value of resulting vector. Compare it with treshold.
 * And increment the value of stepcounter if condition result is true.
 * In other case add the value of total vector to variable half_step(unused)
 */
void calc_of_steps(int16_t *total_v, int16_t *previous_v, uint16_t *step_count, const int *tres_hold)
{
	mtb_bmi160_data_t data;
	mtb_bmi160_read(&motion_sensor, &data);
	//static uint16_t half_step; //Variable for accounting of half steps(unused)
	int16_t vector = sqrt( (data.accel.x*data.accel.x) + (data.accel.y*data.accel.y) + (data.accel.z*data.accel.z) );//
	(* total_v) = vector - (* previous_v);

    /* Operators that account half steps during walking.
     * Not used due to measurement errors */
	/*
	if((fabs((* total_v)) > (* tres_hold)) || (half_step > (* tres_hold)))
	{
		 (* step_count)++;
		 half_step = 0;
    }
	else
	{
	      half_step += (* total_v); //account for half
	}
	*/

	if((fabs((* total_v)) > (* tres_hold)))
	{
	    (* step_count)++;
	}
	(* previous_v) = vector;
}

/* Function that initialize peripherals for using EINK display */
void eink_init(cy_rslt_t result)
{
	  result = cyhal_spi_init(&spi, CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MOSI,
	    	   CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MISO,
	           CY8CKIT_028_EPD_PIN_DISPLAY_SPI_SCLK, NC, NULL, 8,
	           CYHAL_SPI_MODE_00_MSB, false);
	    if (CY_RSLT_SUCCESS == result)
	    {
	        result = cyhal_spi_set_frequency(&spi, 20000000);
	    }
	    result = mtb_e2271cs021_init(&pins, &spi);
	    current_frame = (uint8_t*)LCD_GetDisplayBuffer();
	    GUI_Init();
	    GUI_SetTextMode(GUI_TM_NORMAL);
	    GUI_SetFont(GUI_FONT_32B_1);
	    GUI_SetBkColor(GUI_WHITE);
	    GUI_SetColor(GUI_BLACK);
	    GUI_SetTextAlign(GUI_ALIGN_HCENTER | GUI_ALIGN_HCENTER);
}

/* Function that initialize peripherals for using BMI160 motion sensor */
void bmi_init(cy_rslt_t result)
{
	result = cyhal_i2c_init(&i2c, IMU_I2C_SDA, IMU_I2C_SCL, NULL);
	    CY_ASSERT(result == CY_RSLT_SUCCESS);
	    result = cyhal_i2c_configure(&i2c, &i2c_cfg);
	    CY_ASSERT(result == CY_RSLT_SUCCESS);
	    /* Initialize motion sensor */
	    result = mtb_bmi160_init_i2c(&motion_sensor, &i2c, MTB_BMI160_DEFAULT_ADDRESS);
	    CY_ASSERT(result == CY_RSLT_SUCCESS);
}
