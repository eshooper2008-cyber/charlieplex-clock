// PROJECT  : CharlieClock (RTC)(STM32)
// PURPOSE  :  Use RTC and intergrated PCBs to control a CharlieClock using multiplexing
// COURSE   :ICD2O
// AUTHOR   : Elliott Hooper
// DATE     :2025 October 4
// MCU      : STM32F411CEU6
// STATUS   :Working

#include "main.h" // Standard STM32 include

// Struct for representing an LED by anode/cathode pins
struct LED {
    uint16_t anode;
    uint16_t cathode;
};
// Array of all possible LED connections for seconds, minutes, hours
struct LED CLOCK[] = {
   {GPIO_PIN_10, GPIO_PIN_7},    // {P1, P5}
   {GPIO_PIN_8, GPIO_PIN_7},     // {P2, P5}
   {GPIO_PIN_9, GPIO_PIN_7},     // {P3, P5}
   {GPIO_PIN_15, GPIO_PIN_7},    // {P4, P5}
   {GPIO_PIN_4, GPIO_PIN_7},     // {P6, P5}
   {GPIO_PIN_5, GPIO_PIN_7},     // {P7, P5}
   {GPIO_PIN_6, GPIO_PIN_7},     // {P8, P5}
   {GPIO_PIN_3, GPIO_PIN_7},     // {P9, P5}
   {GPIO_PIN_2, GPIO_PIN_7},     // {P10, P5}
   {GPIO_PIN_1, GPIO_PIN_7},     // {P11, P5}
   {GPIO_PIN_0, GPIO_PIN_7},     // {P12, P5}
   {GPIO_PIN_6, GPIO_PIN_15},    // {P8, P4}
   {GPIO_PIN_3, GPIO_PIN_15},    // {P9, P4}
   {GPIO_PIN_2, GPIO_PIN_15},    // {P10, P4}
   {GPIO_PIN_1, GPIO_PIN_15},    // {P11, P4}
   {GPIO_PIN_0, GPIO_PIN_15},    // {P12, P4}
   {GPIO_PIN_0, GPIO_PIN_3},     // {P12, P9}
   {GPIO_PIN_1, GPIO_PIN_3},     // {P11, P9}
   {GPIO_PIN_2, GPIO_PIN_3},     // {P10, P9}
   {GPIO_PIN_6, GPIO_PIN_3},     // {P8, P9}
   {GPIO_PIN_5, GPIO_PIN_3},     // {P7, P9}
   {GPIO_PIN_4, GPIO_PIN_3},     // {P6, P9}
   {GPIO_PIN_7, GPIO_PIN_3},     // {P5, P9}
   {GPIO_PIN_15, GPIO_PIN_3},    // {P4, P9}
   {GPIO_PIN_9, GPIO_PIN_3},     // {P3, P9}
   {GPIO_PIN_8, GPIO_PIN_3},     // {P2, P9}
   {GPIO_PIN_10, GPIO_PIN_3},    // {P1, P9}
   {GPIO_PIN_0, GPIO_PIN_6},     // {P12, P8}
   {GPIO_PIN_1, GPIO_PIN_6},     // {P11, P8}
   {GPIO_PIN_2, GPIO_PIN_6},     // {P10, P8}
   {GPIO_PIN_3, GPIO_PIN_6},     // {P9, P8}
   {GPIO_PIN_5, GPIO_PIN_6},     // {P7, P8}
   {GPIO_PIN_4, GPIO_PIN_6},     // {P6, P8}
   {GPIO_PIN_7, GPIO_PIN_6},     // {P5, P8}
   {GPIO_PIN_15, GPIO_PIN_6},    // {P4, P8}
   {GPIO_PIN_9, GPIO_PIN_6},     // {P3, P8}
   {GPIO_PIN_8, GPIO_PIN_6},     // {P2, P8}
   {GPIO_PIN_10, GPIO_PIN_6},    // {P1, P8}
   {GPIO_PIN_0, GPIO_PIN_5},     // {P12, P7}
   {GPIO_PIN_1, GPIO_PIN_5},     // {P11, P7}
   {GPIO_PIN_2, GPIO_PIN_5},     // {P10, P7}
   {GPIO_PIN_3, GPIO_PIN_5},     // {P9, P7}
   {GPIO_PIN_6, GPIO_PIN_5},     // {P8, P7}
   {GPIO_PIN_4, GPIO_PIN_5},     // {P6, P7}
   {GPIO_PIN_7, GPIO_PIN_5},     // {P5, P7}
   {GPIO_PIN_15, GPIO_PIN_5},    // {P4, P7}
   {GPIO_PIN_9, GPIO_PIN_5},     // {P3, P7}
   {GPIO_PIN_8, GPIO_PIN_5},     // {P2, P7}
   {GPIO_PIN_10, GPIO_PIN_5},    // {P1, P7}
   {GPIO_PIN_10, GPIO_PIN_4},    // {P1, P6}
   {GPIO_PIN_8, GPIO_PIN_4},     // {P2, P6}
   {GPIO_PIN_9, GPIO_PIN_4},     // {P3, P6}
   {GPIO_PIN_15, GPIO_PIN_4},    // {P4, P6}
   {GPIO_PIN_7, GPIO_PIN_4},     // {P5, P6}
   {GPIO_PIN_5, GPIO_PIN_4},     // {P7, P6}
   {GPIO_PIN_6, GPIO_PIN_4},     // {P8, P6}
   {GPIO_PIN_3, GPIO_PIN_4},     // {P9, P6}
   {GPIO_PIN_2, GPIO_PIN_4},     // {P10, P6}
   {GPIO_PIN_1, GPIO_PIN_4},     // {P11, P6}
   {GPIO_PIN_0, GPIO_PIN_4},     // {P12, P6}
   {GPIO_PIN_6, GPIO_PIN_8},     // {P8, P2}
   {GPIO_PIN_3, GPIO_PIN_8},     // {P9, P2}
   {GPIO_PIN_2, GPIO_PIN_8},     // {P10, P2}
   {GPIO_PIN_1, GPIO_PIN_8},     // {P11, P2}
   {GPIO_PIN_0, GPIO_PIN_8},     // {P12, P2}
   {GPIO_PIN_10, GPIO_PIN_0},    // {P1, P12}
   {GPIO_PIN_8, GPIO_PIN_0},     // {P2, P12}
   {GPIO_PIN_9, GPIO_PIN_0},     // {P3, P12}
   {GPIO_PIN_15, GPIO_PIN_0},    // {P4, P12}
   {GPIO_PIN_7, GPIO_PIN_0},     // {P5, P12}
   {GPIO_PIN_4, GPIO_PIN_0},     // {P6, P12}
   {GPIO_PIN_5, GPIO_PIN_0},     // {P7, P12}
   {GPIO_PIN_6, GPIO_PIN_0},     // {P8, P12}
   {GPIO_PIN_3, GPIO_PIN_0},     // {P9, P12}
   {GPIO_PIN_2, GPIO_PIN_0},     // {P10, P12}
   {GPIO_PIN_1, GPIO_PIN_0},     // {P11, P12}
   {GPIO_PIN_2, GPIO_PIN_1},     // {P10, P11}
   {GPIO_PIN_3, GPIO_PIN_1},     // {P9, P11}
   {GPIO_PIN_6, GPIO_PIN_1},     // {P8, P11}
   {GPIO_PIN_5, GPIO_PIN_1},     // {P7, P11}
   {GPIO_PIN_4, GPIO_PIN_1},     // {P6, P11}
   {GPIO_PIN_7, GPIO_PIN_1},     // {P5, P11}
   {GPIO_PIN_15, GPIO_PIN_1},    // {P4, P11}
   {GPIO_PIN_9, GPIO_PIN_1},     // {P3, P11}
   {GPIO_PIN_8, GPIO_PIN_1},     // {P2, P11}
   {GPIO_PIN_10, GPIO_PIN_1},    // {P1, P11}
   {GPIO_PIN_0, GPIO_PIN_2},     // {P12, P10}
   {GPIO_PIN_1, GPIO_PIN_2},     // {P11, P10}
   {GPIO_PIN_3, GPIO_PIN_2},     // {P9, P10}
   {GPIO_PIN_6, GPIO_PIN_2},     // {P8, P10}
   {GPIO_PIN_5, GPIO_PIN_2},     // {P7, P10}
   {GPIO_PIN_4, GPIO_PIN_2},     // {P6, P10}
   {GPIO_PIN_7, GPIO_PIN_2},     // {P5, P10}
   {GPIO_PIN_15, GPIO_PIN_2},    // {P4, P10}
   {GPIO_PIN_9, GPIO_PIN_2},     // {P3, P10}
   {GPIO_PIN_8, GPIO_PIN_2},     // {P2, P10}
   {GPIO_PIN_10, GPIO_PIN_2},    // {P1, P10}
   {GPIO_PIN_5, GPIO_PIN_15},    // {P7, P4}
   {GPIO_PIN_4, GPIO_PIN_15},    // {P6, P4}
   {GPIO_PIN_7, GPIO_PIN_15},    // {P5, P4}
   {GPIO_PIN_9, GPIO_PIN_15},    // {P3, P4}
   {GPIO_PIN_6, GPIO_PIN_15},    // {P2, P4}
   {GPIO_PIN_10, GPIO_PIN_15},   // {P1, P4}
   {GPIO_PIN_10, GPIO_PIN_9},    // {P1, P3}
   {GPIO_PIN_8, GPIO_PIN_9},     // {P2, P3}
   {GPIO_PIN_15, GPIO_PIN_9},    // {P4, P3}
   {GPIO_PIN_7, GPIO_PIN_9},     // {P5, P3}
   {GPIO_PIN_4, GPIO_PIN_9},     // {P6, P3}
   {GPIO_PIN_5, GPIO_PIN_9},     // {P7, P3}
   {GPIO_PIN_6, GPIO_PIN_9},     // {P8, P3}
   {GPIO_PIN_3, GPIO_PIN_9},     // {P9, P3}
   {GPIO_PIN_2, GPIO_PIN_9},     // {P10, P3}
   {GPIO_PIN_1, GPIO_PIN_9},     // {P11, P3}
   {GPIO_PIN_0, GPIO_PIN_9},     // {P12, P3}
   {GPIO_PIN_10, GPIO_PIN_6},    // {P1, P2}
   {GPIO_PIN_9, GPIO_PIN_6},     // {P3, P2}
   {GPIO_PIN_15, GPIO_PIN_6},    // {P4, P2}
   {GPIO_PIN_7, GPIO_PIN_6},     // {P5, P2}
   {GPIO_PIN_4, GPIO_PIN_6},     // {P6, P2}
   {GPIO_PIN_5, GPIO_PIN_6},     // {P7, P2}
   {GPIO_PIN_3, GPIO_PIN_10},    // {P9, P1}
   {GPIO_PIN_2, GPIO_PIN_10},    // {P10, P1}
   {GPIO_PIN_1, GPIO_PIN_10},    // {P11, P1}
   {GPIO_PIN_0, GPIO_PIN_10},    // {P12, P1}
   {GPIO_PIN_0, GPIO_PIN_1},     // {P12, P11}
   {GPIO_PIN_7, GPIO_PIN_10},    // {P5, P1}
   {GPIO_PIN_15, GPIO_PIN_10},   // {P4, P1}
   {GPIO_PIN_9, GPIO_PIN_10},    // {P3, P1}
   {GPIO_PIN_8, GPIO_PIN_10},    // {P2, P1}
   {GPIO_PIN_4, GPIO_PIN_10},    // {P6, P1}
   {GPIO_PIN_5, GPIO_PIN_10},    // {P7, P1}
   {GPIO_PIN_6, GPIO_PIN_10},    // {P8, P1}
};

RTC_HandleTypeDef hrtc;                         // RTC peripheral handle

uint8_t sec = 0, min = 0, hour = 0;             // Current RTC time
uint8_t set_sec = 0, set_min = 0, set_hour = 0; // Time being set (user editable)
volatile uint8_t my_interrupt_count = 0;        // State variable, set mode or display mode

void SystemClock_Config(void);      // STM32Cube sets up system clock (handled by STM32Cube)
static void MX_GPIO_Init(void);     // STM32Cube sets up GPIO (handled by STM32Cube)
static void MX_RTC_Init(void);      // STM32Cube sets up RTC (handled by STM32Cube)

// Turn off all LEDs by making all segment pins digital inputs
void Clear(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};                // Structure to configure GPIO
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                // Set mode to input
    GPIO_InitStruct.Pull = GPIO_NOPULL;                    // No pullup/pulldown 
    uint16_t pins[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
        GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
        GPIO_PIN_10, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_15}; // All relevant PA lines
    for (int i = 0; i < 12; i++) {                         // Loop through all lines
        GPIO_InitStruct.Pin = pins[i];                     // Set the current pin
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);            // Reconfigure as input
    }
}

// Set a single LED by making both pins outputs, one high (anode), one low (cathode)
void Set(int pos, int neg) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};                // Structure for GPIO setup
    GPIO_InitStruct.Pin = pos | neg;                       // Both pins to output
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            // Push-pull output
    GPIO_InitStruct.Pull = GPIO_NOPULL;                    // No pull
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                // Set both as outputs
    HAL_GPIO_WritePin(GPIOA, pos, GPIO_PIN_SET);           // Anode pin high
    HAL_GPIO_WritePin(GPIOA, neg, GPIO_PIN_RESET);         // Cathode pin low
}

// Show current RTC time by lighting correct LED for seconds, minutes, and hours (one at a time for multiplexing)
void DisplayTime() {
    Clear();                                                        // Turn off all
    Set(CLOCK[sec].anode, CLOCK[sec].cathode);                      // Show active second
    HAL_Delay(2);                                                   // Hold briefly

    Clear();                                                        // Turn off all
    Set(CLOCK[60 + min].anode, CLOCK[60 + min].cathode);            // Show active minute
    HAL_Delay(2);                                                   // Hold briefly

    Clear();                                                        // Turn off all
    Set(CLOCK[120 + ((hour) % 12)].anode, CLOCK[120 + ((hour) % 12)].cathode); // Show hour (mod 12 for position)
    HAL_Delay(2);                                                   // Hold briefly
}

// Show the "set" (user editable) time while setting
void DisplaySetTime() {
    Clear();                                                          // Turn off all
    Set(CLOCK[set_sec].anode, CLOCK[set_sec].cathode);                // Set second
    HAL_Delay(2);

    Clear();
    Set(CLOCK[60 + set_min].anode, CLOCK[60 + set_min].cathode);      // Set minute
    HAL_Delay(2);

    Clear();
    Set(CLOCK[120 + ((set_hour) % 12)].anode, CLOCK[120 + ((set_hour) % 12)].cathode); // Set hour
    HAL_Delay(2);
}

int main(void)
{
  HAL_Init();                          // HAL system/init
  SystemClock_Config();                // Core/system clock (handled by STM32Cube)
  MX_GPIO_Init();                      // GPIO (handled by STM32Cube)
  MX_RTC_Init();                       // RTC (handled by STM32Cube)

  uint8_t prev_pb13 = 1, prev_pb14 = 1;// Track last button state for deglitch/edge
  RTC_TimeTypeDef sTime = {0};         // Struct for retrieving RTC time
  RTC_DateTypeDef sDate = {0};         // Struct for retrieving RTC date

  while (1)
  {
      if(my_interrupt_count == 0){                                 // In display mode (default)
          HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);          // Read RTC current time into sTime
          HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);          // (Must call after gettime)
          sec = sTime.Seconds;                                     // Update vars from struct
          min = sTime.Minutes;
          hour = sTime.Hours;
          DisplayTime();                                           // Update LEDs for actual time
      }
      else if(my_interrupt_count == 1){                            // In "set" mode for user entry
          DisplaySetTime();                                        // Show editable time on LEDs

          uint8_t curr_pb13 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13); // PB13 edge for incrementing hour
          if(prev_pb13 == 1 && curr_pb13 == 0){                     // If pressed (falling edge detected)
              set_hour++;                                           // Increment hour
              if(set_hour > 23) set_hour = 0;                       // Wrap to 0 after 23
          }
          prev_pb13 = curr_pb13;                                    // Save last state

          static uint32_t pb14_press_ticks = 0;                     // Ticks for long-press MIN
          static uint32_t last_tick = 0;                            // Used for repeat speed MIN
          uint8_t curr_pb14 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14); // PB14 for incrementing minute

          if(prev_pb14 == 1 && curr_pb14 == 0){                     // Press detected on MIN button
              set_min++;                                            // Increment min
              if(set_min >= 60) set_min = 0;                        // Wrap at 60
              pb14_press_ticks = HAL_GetTick();                     // Store tick time
          }
          else if(curr_pb14 == 0){                                  // HOLD detected
              uint32_t now = HAL_GetTick();                         // Get ticks now
              if(now - pb14_press_ticks > 500 && now - last_tick > 100){
                  set_min++;                                        // Increment again if long hold
                  if(set_min >= 60) set_min = 0;                    // Wrap at 60
                  last_tick = now;                                  // Update auto-increment mark
              }
          }
          else{                                                     // Not pressed
              pb14_press_ticks = 0;
              last_tick = 0;
          }
          prev_pb14 = curr_pb14;                                    // Save last MIN state
      }
      // RTC is only written in EXTI callback below (PB12)
  }
}

// Handles the user button on PB12 (EXTI): toggles set/display mode, writes time when leaving set
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);         // Handle pin interrupt (calls user callback)
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_12)                                  // Check PB12 sourced the interrupt
    {
        my_interrupt_count = (my_interrupt_count + 1) % 2;       // Toggle mode
        if(my_interrupt_count == 0){                             // If now leaving "set" mode
            RTC_TimeTypeDef sTime;
            sTime.Hours = set_hour;                              // Set hour from user val
            sTime.Minutes = set_min;                             // Set minute from user val
            sTime.Seconds = set_sec;                             // Set second from user val
            sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;      // No DST
            sTime.StoreOperation = RTC_STOREOPERATION_RESET;     // No store op
            if(HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
                Error_Handler();                                 // Halt if error
            }
        }
    }
}

// All configuration and setup functions below are handled by STM32Cube generated code.
void SystemClock_Config(void)
{
  // All hardware system clock setup is handled by STM32Cube-generated code.
}
static void MX_RTC_Init(void)
{
  // All hardware RTC peripheral setup is handled by STM32Cube-generated code.
}
static void MX_GPIO_Init(void)
{
  // All GPIO setup (mode, speed, pull, etc) is handled by STM32Cube-generated code.
}
void Error_Handler(void)
{
  __disable_irq();
  while (1) { }
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) { }
#endif /* USE_FULL_ASSERT */

