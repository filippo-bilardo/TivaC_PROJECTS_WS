

#ifndef FBCP_H_
#define FBCP_H_

//------------------------------------------------------------------------------------------
//=== Function prototypes ==================================================================
//------------------------------------------------------------------------------------------
void L1_2_PcToMicro_Init(void);
void L1_2_PcToMicro_Rx_Task(void);
void L7_PcToMicro_Task(void);
void L1_MicroToMicro_Init(void);
void L1_MicroToMicro_RxTask(void);
void L1_MicroToMicro_TxTask(void);

#endif /* FBCP_H_ */
