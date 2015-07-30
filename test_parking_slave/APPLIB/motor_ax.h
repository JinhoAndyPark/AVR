#ifndef __AX_H
#define __AX_H

//------------------------------------------------------------------------------
//					--- Control Table Address ---
//							EEPROM AREA
//------------------------------------------------------------------------------
#define P_MODEL_NUMBER_L      0
#define P_MODOEL_NUMBER_H     1
#define P_VERSION             2
#define P_ID                  3
#define P_BAUD_RATE           4
#define P_RETURN_DELAY_TIME   5
#define P_CW_ANGLE_LIMIT_L    6
#define P_CW_ANGLE_LIMIT_H    7
#define P_CCW_ANGLE_LIMIT_L   8
#define P_CCW_ANGLE_LIMIT_H   9
#define P_SYSTEM_DATA2        10
#define P_LIMIT_TEMPERATURE   11
#define P_DOWN_LIMIT_VOLTAGE  12
#define P_UP_LIMIT_VOLTAGE    13
#define P_MAX_TORQUE_L        14
#define P_MAX_TORQUE_H        15
#define P_RETURN_LEVEL        16
#define P_ALARM_LED           17
#define P_ALARM_SHUTDOWN      18
#define P_OPERATING_MODE      19
#define P_DOWN_CALIBRATION_L  20
#define P_DOWN_CALIBRATION_H  21
#define P_UP_CALIBRATION_L    22
#define P_UP_CALIBRATION_H    23
//------------------------------------------------------------------------------
//					--- Control Table Address ---
//							 RAM AREA
//------------------------------------------------------------------------------
#define P_TORQUE_ENABLE         (24)
#define P_LED                   (25)
#define P_CW_COMPLIANCE_MARGIN  (26)
#define P_CCW_COMPLIANCE_MARGIN (27)
#define P_CW_COMPLIANCE_SLOPE   (28)
#define P_CCW_COMPLIANCE_SLOPE  (29)
#define P_GOAL_POSITION_L       (30)
#define P_GOAL_POSITION_H       (31)
#define P_GOAL_SPEED_L          (32)
#define P_GOAL_SPEED_H          (33)
#define P_TORQUE_LIMIT_L        (34)
#define P_TORQUE_LIMIT_H        (35)
#define P_PRESENT_POSITION_L    (36)
#define P_PRESENT_POSITION_H    (37)
#define P_PRESENT_SPEED_L       (38)
#define P_PRESENT_SPEED_H       (39)
#define P_PRESENT_LOAD_L        (40)
#define P_PRESENT_LOAD_H        (41)
#define P_PRESENT_VOLTAGE       (42)
#define P_PRESENT_TEMPERATURE   (43)
#define P_REGISTERED_INSTRUCTION (44)
#define P_PAUSE_TIME            (45)
#define P_MOVING (46)
#define P_LOCK                  (47)
#define P_PUNCH_L               (48)
#define P_PUNCH_H               (49)
//------------------------------------------------------------------------------
//						--- Instruction ---
//------------------------------------------------------------------------------
#define INST_PING           0x01
#define INST_READ           0x02
#define INST_WRITE          0x03
#define INST_REG_WRITE      0x04
#define INST_ACTION         0x05
#define INST_RESET          0x06
#define INST_SYNC_WRITE     0x83
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#define CLEAR_BUFFER RxBufferReadPointer = RxBufferWritePointer
#define DEFAULT_RETURN_PACKET_SIZE 6
#define BROADCASTING_ID 0xfe

#define TxD8 TxD81
#define RxD8 RxD81


#define DEFAULT_BAUD_RATE 1                 //57600bps at 16MHz

////// For CM-5
#define RS485_TXD /*PORTE &= ~(1<<PE3),*/PORTE |= (1<<PE2)  //PORT_485_DIRECTION = 1
#define RS485_RXD PORTE &= (1<<PE2)/*,PORTE |= (1<<PE3)*/  //PORT_485_DIRECTION = 0


#define SET_TXD0_FINISH   sbi(UCSR0A,6)
#define RESET_TXD0_FINISH cbi(UCSR0A,6)
#define CHECK_TXD0_FINISH (UCSR0A & (1<<TXC0))

#define SET_TxD1_FINISH   sbi(UCSR1A,6)
#define RESET_TXD1_FINISH cbi(UCSR1A,6)
#define CHECK_TXD1_FINISH (UCSR1A & (1<<TXC1))

#define RX_INTERRUPT 0x01
#define TX_INTERRUPT 0x02
#define OVERFLOW_INTERRUPT 0x01
#define SERIAL_PORT0 0
#define SERIAL_PORT1 1
#define BIT_Uart_DIRECTION0  0x08  //Port E
#define BIT_Uart_DIRECTION1  0x04  //Port E

//------------------------------------------------------------------------------
//			    	            --- TXD / RXD  ---
//------------------------------------------------------------------------------
#define TXD1_READY			(UCSR1A & (1<<UDRE1))
#define TXD1_DATA			(UDR1)
#define RXD1_READY			(UCSR1A & (1<<RXC1))
#define RXD1_DATA			(UDR1)

#define TXD0_READY			(UCSR0A & (1<<UDRE0))
#define TXD0_DATA			(UDR0)
#define RXD0_READY			(UCSR0A & (1<<RXC0))

//------------------------------------------------------------------------------
//						--- DX 함수선언 ---
//------------------------------------------------------------------------------
U08 TxPacket(U08 ID, U08 Instruction, U08 ParameterLength);
U08 RxPacket(U08 RxPacketLength);
void TxD8Hex(U08 SentData);
void PrintBuffer(U08 *PrintBuffer, U08 Length);
void AX_Action(U08 ID, U08 Position_H, U08 Position_L, U08 Speed_H, U08 Speed_L);

#endif
